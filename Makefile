# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=boot.o main.o common.o screen.o gdt.o idt.o isrs.o irq.o timer.o kb.o kheap.o paging.o ordered_array.o fs.o initrd.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -Iinclude
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

iso:
	isofiles/geniso.sh

run:
	qemu -cdrom isofiles/glados.iso

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
