#include "fs.h"

int INE5412_FS::fs_format()
{
	return 0;
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
	return 0;
}

int INE5412_FS::fs_create()
{
	return 0;
}

int INE5412_FS::fs_delete(int inumber)
{
	return 0;
}

int INE5412_FS::fs_getsize(int inumber)
{
	return -1;
}

int INE5412_FS::fs_read(int inumber, char *data, int length, int offset)
{
	return 0;
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{
	return 0;
}
