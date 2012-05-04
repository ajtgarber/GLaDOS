// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include <common.h>
#include <multiboot.h>
#include <screen.h>
#include <kheap.h>
#include <paging.h>
#include <fs.h>
#include <initrd.h>

extern u32int placement_address;

int main(multiboot_header_t *mboot_ptr)
{
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	//timer_install();
	keyboard_install();
	init_video();

	ASSERT(mboot_ptr->mods_count > 0);
	u32int initrd_location = *((u32int*)mboot_ptr->mods_addr);
	u32int initrd_end = *(u32int*)(mboot_ptr->mods_addr+4);
	//Don't trample our module with placement addresses, please!
	placement_address = initrd_end;

	initialise_paging();
	sti();

	fs_root = initialise_initrd(initrd_location);

	puts("Testing initrd...\n");
	puts("Location of fs_root: ");
	puthex(fs_root);
	puts("\n");
	puts("Listing contents of /\n");
	// list the contents of /
	int i = 0;
	struct dirent *node = 0;
	while ( (node = readdir_fs(fs_root, i)) != 0) {
  		puts("Found file ");
  		puts(node->name);
  		fs_node_t *fsnode = finddir_fs(fs_root, node->name);

  		if ((fsnode->flags&0x7) == FS_DIRECTORY)
    		puts("\n\t(directory)\n");
  		else {
    		puts("\n\t contents: \"");
    		char buf[256];
    		u32int sz = read_fs(fsnode, 0, 256, buf);
    		int j;
    		for (j = 0; j < sz; j++)
      			putch(buf[j]);

    		puts("\"\n");
  		}
  		i++;
	}

	puts("GLaDOS v sqrt(-1) started... beware (of bugs)\n");
	puts("> ");

	for(;;);

	// All our initialisation calls will go in here.
	return 0xDEADBABA;
}
