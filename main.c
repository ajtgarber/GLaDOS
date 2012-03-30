// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include <multiboot.h>
#include <common.h>
#include <screen.h>
#include <paging.h>

int main(struct multiboot_info *mboot_ptr)
{
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	//timer_install();
	keyboard_install();
	init_video();
	initialise_paging();

	sti();

	puts("GLaDOS v sqrt(-1) started... beware (of bugs)\n");
	puts("> ");

	for(;;);

    // All our initialisation calls will go in here.
    return 0xDEADBABA;
}
