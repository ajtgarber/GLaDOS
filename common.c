#include <common.h>

void outb(u16int port, u8int value) {
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}
u8int inb(u16int port) {
	u8int ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

u16int inw(u16int port) {
	u16int ret;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

int strlen(char* str) {
	int i;
	for(i = 0; str[i] != 0 ; i++);
	return i;
}

void memset(char* dst, char value, int length) {
	int i;
	for(i = 0; i < length; i++) {
		dst[i] = value;
	}
}
void memsetw(short* dst, short value, int length) {
	int i;
	for(i = 0; i < length; i++) {
		dst[i] = value;
	}
}


void cli() {
	__asm__ __volatile__ ("cli");
}
void sti() {
	__asm__ __volatile__ ("sti");
}
void hlt() {
	__asm__ __volatile__ ("hlt");
}

extern void panic(const char *message, const char *file, u32int line)
{
    // We encountered a massive problem and have to stop.
    cli(); // Disable interrupts.

    puts("PANIC(");
    puts(message);
    puts(") at ");
    puts(file);
    puts(":");
    putdec(line);
    puts("\n----------------------\n");
	puts("Aperture Science....\n");
	puts("This was a trumph....\n");
	puts("I'm making a note here... HUGE SUCCESS!");
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(const char *file, u32int line, const char *desc)
{
    // An assertion failed, and we have to panic.
    cli(); // Disable interrupts.

    puts("ASSERTION-FAILED(");
    puts(desc);
    puts(") at ");
    puts(file);
    puts(":");
    putdec(line);
    puts("\n");
    // Halt by going into an infinite loop.
    for(;;);
}
