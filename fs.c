#include "fs.h"

fs_node_t* fs_root = 0; //The root of the fs

u32int read_fs(fs_node_t* node, u32int offset, u32int size, u8int* buffer) {
	//Has the node got a read callback?
	if(node->read != 0)
		return node->read(node, offset, size, buffer);
	else
		return 0;
}
u32int write_fs(fs_node_t* node, u32int offset, u32int size, u8int* buffer) {
	//Has the node got a write callback?
	if(node->write != 0)
		return node->write(node, offset, size, buffer);
	else
		return 0;
}

struct dirent* readdir_fs(fs_node_t* node, u32int index) {
	if((node->flags & 0x7) == FS_DIRECTORY && node->readdir != 0)
		return node->readdir(node, index);
	else
`		return 0;
}
fs_node_t* finddir_fs(fs_node_t* node, char* name) {
	if((node->flags & 0x7) == FS_DIRECTORY && node->finddir != 0)
		return node->finddir(node, name);
	else
		return 0;
}
