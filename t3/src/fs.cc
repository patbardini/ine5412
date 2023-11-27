#include "fs.h"
#include <math.h>
#include <cstring> 
#include <algorithm>

int INE5412_FS::fs_format()
{
	// verifica se já foi montado
	if (is_mounted) return 0;

	union fs_block block;
	disk->read(0, block.data);

	// libera a tabela de inodos
	for (int i = 0; i < block.super.ninodeblocks; i++) {
		for (int j = 0; j < INODES_PER_BLOCK; j++) {
			block.inode[j].isvalid = 0;
		}
		disk->write(i + 1, block.data);
	}

	int nblocks = disk->size();
	int ninodeblocks = ceil(nblocks * 0.1);	// reserva dez por cento dos blocos para inodos

	// escreve o superbloco
	block.super.magic = FS_MAGIC;
	block.super.nblocks = nblocks;
	block.super.ninodeblocks = ninodeblocks;
	block.super.ninodes = ninodeblocks * INODES_PER_BLOCK;

	disk->write(0, block.data);

	return 1;
}

void INE5412_FS::fs_debug()
{
	union fs_block block;

	disk->read(0, block.data);

	cout << "superblock:\n";
	cout << "    " << (block.super.magic == FS_MAGIC ? "magic number is valid\n" : "magic number is invalid!\n");
 	cout << "    " << block.super.nblocks << " blocks\n";
	cout << "    " << block.super.ninodeblocks << " inode blocks\n";
	cout << "    " << block.super.ninodes << " inodes\n";

	union fs_block inode_block;

	// percorre cada bloco de inode
	for (int i = 0; i < block.super.ninodeblocks; i++) {
		disk->read(i + 1, inode_block.data);

		// percorre cada inode contido no bloco de inode
		for (int j = 0; j < INODES_PER_BLOCK; j++) {

			fs_inode inode = inode_block.inode[j];

			if (inode.isvalid) {
				int inode_number = i * INODES_PER_BLOCK + j;
				cout << "inode " << inode_number << ":\n";
				cout << "    size: " << inode.size << " bytes\n";

				cout << "    direct blocks: ";
				for (int direct_block : inode.direct) {
					if (direct_block) {
						cout << direct_block << " ";
					}
				}
				cout << "\n";

				if (inode.indirect) {
					cout << "    indirect block: " << inode.indirect << "\n";

					union fs_block indirect_block;
					disk->read(inode.indirect, indirect_block.data);

					cout << "    indirect data blocks: ";
					for (int indirect_data_blocks : indirect_block.pointers) {
						if (indirect_data_blocks) {
							cout << indirect_data_blocks << " ";
						}
					}
					cout << "\n";
				}
			}
		}
	}
}

int INE5412_FS::fs_mount()
{
	// lê superbloco para verificar se há um sistema de arquivos
	union fs_block block;

	disk->read(0, block.data);

	if (block.super.magic != FS_MAGIC) return 0;

	// constrói bitmap
	bitmap.resize(block.super.nblocks);
	std::fill(bitmap.begin(), bitmap.end(), 0);

	// ocupa bloco do superbloco
	bitmap[0] = 1;
	// verifica todos os inodes válidos
	union fs_block inode_block;

	for (int i = 0; i < block.super.ninodeblocks; i++) {
		// ocupa blocos dos inodos
		bitmap[i + 1] = 1;

		disk->read(i + 1, inode_block.data);

		for (int j = 0; j < INODES_PER_BLOCK; j++) {

			fs_inode &inode = inode_block.inode[j];

			if (inode.isvalid) {
				for (int direct_block : inode.direct) {
					if (direct_block) bitmap[direct_block] = 1;
				}

				if (inode.indirect) {
					bitmap[inode.indirect] = 1;

					union fs_block indirect_block;
					disk->read(inode.indirect, indirect_block.data);

					for (int indirect_data_blocks : indirect_block.pointers) {
						if (indirect_data_blocks) bitmap[indirect_data_blocks] = 1;
					}
				}
			}
		}
	}

	is_mounted = true;
	return 1;
}

int INE5412_FS::fs_create()
{
	// verifica se já foi montado
	if (!is_mounted) return 0;

	// verifica se há espaço nos blocos de inodo
	union fs_block block;
	disk->read(0, block.data);

	union fs_block inode_block;

	for (int i = 0; i < block.super.ninodeblocks; i++) {
		disk->read(i + 1, inode_block.data);

		for (int j = 1; j < INODES_PER_BLOCK + 1; j++) {

			fs_inode &inode = inode_block.inode[j];

			if (!inode.isvalid) {
				int inumber = i * INODES_PER_BLOCK + j;
				
				inode.isvalid = 1;
				inode.size = 0;
				inode.indirect = 0;
				for (int &direct_block : inode.direct) {
					direct_block = 0;
				}

				this->inode_save(inumber, &inode);

				return inumber;
			}
		}
	}
	
	return 0;
}

int INE5412_FS::fs_delete(int inumber)
{
	// verifica se está montado
	if (!is_mounted) {
		cout << "ERROR: disk is not mounted\n";
		return 0;
	}

	fs_inode inode;
	if (this->inode_load(inumber, &inode) && inode.isvalid) {

		for (int &direct_block : inode.direct) {
			direct_block = 0;
			bitmap[direct_block] = 0;
		}

		if (inode.indirect) {
			union fs_block indirect_block;
			disk->read(inode.indirect, indirect_block.data);

			for (int &indirect_data_blocks : indirect_block.pointers) {
				indirect_data_blocks = 0;
				bitmap[indirect_data_blocks] = 0;
			}

			bitmap[inode.indirect] = 0;
		}

		inode.isvalid = 0;
		inode.size = 0;

		this->inode_save(inumber, &inode);

		return 1;
	}
	return 0;
}

int INE5412_FS::fs_getsize(int inumber)
{
	if (!is_mounted) {
		cout << "ERROR: disk is not mounted\n";
		return -1;
	}

	fs_inode inode;
	if (this->inode_load(inumber, &inode) && inode.isvalid) {
		return inode.size;
	}

	return -1;
}

int INE5412_FS::fs_read(int inumber, char *data, int length, int offset)
{
	// verifica se disco está montado
	if (!is_mounted) {
		cout << "ERROR: disk is not mounted\n";
		return 0;
	}

	// carrega o inodo correspondente ao inumber e verifica se ele é válido
	fs_inode inode;
	if (this->inode_load(inumber, &inode) && inode.isvalid) {

		int bytes_read = 0;
		int remaining_length = length;

		int block_num;
		union fs_block block;

		// lê os dados do inodo, começando do offset até o comprimento especificado
		while (remaining_length > 0 && offset < inode.size) {
			block_num = offset / Disk::DISK_BLOCK_SIZE;

			if (block_num < POINTERS_PER_INODE) {
				// lê dos blocos diretos
				disk->read(inode.direct[block_num], block.data);
			} else {
				// lê dos blocos indiretos
				int indirect_index = block_num - POINTERS_PER_INODE;
				union fs_block indirect_block;
				disk->read(inode.indirect, indirect_block.data);
				disk->read(indirect_block.pointers[indirect_index], block.data);
			}

			int block_num = offset % Disk::DISK_BLOCK_SIZE;
			int bytes_to_copy = std::min(Disk::DISK_BLOCK_SIZE - block_num, remaining_length);
			bytes_to_copy = std::min(bytes_to_copy, inode.size - offset);

			memcpy(data + bytes_read, block.data + block_num, bytes_to_copy);

			bytes_read += bytes_to_copy;
			remaining_length -= bytes_to_copy;
			offset += bytes_to_copy;
		}
		// retorna o número total de bytes lidos
		return bytes_read;
	}

	return 0;
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{
	// verifica se disco está montado
	if (!is_mounted) {
		cout << "ERROR: disk is not mounted\n";
		return 0;
	}

	union fs_block block;
	fs_inode inode;
	union fs_block indirect_block;
    
    if (this->inode_load(inumber, &inode) && inode.isvalid) {
		
		int bytes_written = 0;
		int remaining_length = length;
		int blocknum_to_read_from_disk;

        while (remaining_length > 0) {

			int block_num = offset / Disk::DISK_BLOCK_SIZE;
        	int block_index = offset % Disk::DISK_BLOCK_SIZE;

            if (block_num < POINTERS_PER_INODE) {
				// se ainda tiver blocos diretos livres, escreve nestes
                if (!inode.direct[block_num]) {
                    int new_block = this->find_free_block();
                    if (new_block == -1) break;

                    inode.direct[block_num] = new_block;
                }
				blocknum_to_read_from_disk = inode.direct[block_num];

            } else {
                // se não, escreve nos blocos indiretos
                if (!inode.indirect) {
                    int new_block = this->find_free_block();
                    if (new_block == -1) break;

                    inode.indirect = new_block;
                }

                disk->read(inode.indirect, indirect_block.data);

                int indirect_index = block_num - POINTERS_PER_INODE;

                if (!indirect_block.pointers[indirect_index]) {
                    int new_block = this->find_free_block();
                    if (new_block == -1) break;

                    indirect_block.pointers[indirect_index] = new_block;

                    disk->write(inode.indirect, indirect_block.data);
                }
				blocknum_to_read_from_disk = indirect_block.pointers[indirect_index];
			}

			disk->read(blocknum_to_read_from_disk, block.data);

			int bytes_to_copy = std::min(remaining_length, Disk::DISK_BLOCK_SIZE - block_index);
			memcpy(block.data + block_index, data + bytes_written, bytes_to_copy);

			disk->write(block_num < POINTERS_PER_INODE ? inode.direct[block_num] : indirect_block.pointers[block_num - POINTERS_PER_INODE], block.data);

			bytes_written += bytes_to_copy;
			remaining_length -= bytes_to_copy;
			offset += bytes_to_copy;
		}

		// atualiza o tamanho do inodo, caso necessário
		if (inode.size < offset) {
			inode.size = offset;
			this->inode_save(inumber, &inode);
		}

		return bytes_written;
    }
	return 0;
}

int INE5412_FS::inode_load(int inumber, class fs_inode *inode) 
{
	union fs_block block;

	disk->read(0, block.data);

	if (1 > inumber || inumber > block.super.ninodes) {
		cout << "ERROR: invalid inumber\n";
		return 0;
	}

	union fs_block inode_block;

	for (int i = 0; i < block.super.ninodeblocks; i++) {
		// lê bloco que contém o inodo
		disk->read(i + 1, inode_block.data);

		for (int j = 0; j < INODES_PER_BLOCK; j++) {
			if ((i * INODES_PER_BLOCK + j) == inumber) {
				*inode = inode_block.inode[j];
			}
		}
	}
	return 1;
}

int INE5412_FS::inode_save(int inumber, class fs_inode *inode) 
{
	union fs_block block;

	disk->read(0, block.data);

	if (1 > inumber || inumber > block.super.ninodes) {
		cout << "ERROR: invalid inumber\n";
		return 0;
	}

	union fs_block inode_block;

	for (int i = 0; i < block.super.ninodeblocks; i++) {
		// lê bloco que contém o inodo
		disk->read(i + 1, inode_block.data);

		for (int j = 0; j < INODES_PER_BLOCK; j++) {
			if ((i * INODES_PER_BLOCK + j) == inumber) {
				inode_block.inode[j] = *inode;
				break;
			}
		}
		// escreve no disco
		disk->write(i + 1, inode_block.data);
	}
	return 1;
}

// função auxiliar para encontrar um bloco livre
int INE5412_FS::find_free_block() {
	union fs_block block;

	disk->read(0, block.data);

	for (int i = 0; i < block.super.nblocks; i++) {
		if (!bitmap[i]) {
			bitmap[i] = 1;  // marca o bloco como ocupado
			return i;
		}
	}
    return -1;  // retorna -1 caso nenhum bloco livre seja encontrado
}
