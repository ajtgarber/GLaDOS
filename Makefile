# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=boot.o main.o common.o screen.o gdt.o idt.o isrs.o irq.o timer.o kb.o kheap.o paging.o ordered_array.o fs.o initrd.o process.o task.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -Iinclude -m32
LDFLAGS=-melf_i386 -Tlink.ld
ASFLAGS=-felf32

all: $(SOURCES) link

iso:
	cp tools/initrd.img isofiles/boot/boot/
	cp kernel isofiles/boot/boot/
	isofiles/geniso.sh

run:
	qemu-system-i386 -cdrom isofiles/glados.iso

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
