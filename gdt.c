#include <system.h>

struct gdt_entry {
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;  // 0 = 1 byte, 1 = 4KB
	unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

//Our GDT with 3 entries, and our GDT pointer
struct gdt_entry gdt[3];
struct gdt_ptr gp;

extern void gdt_flush();

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
	//setup the descriptor base address
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) && 0xFF;

	//setup the descriptor limits
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);

	//finally set up granularity and access flags
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

void gdt_install() {
	gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
	gp.base = &gdt;

	//null descriptor
	gdt_set_gate(0, 0, 0, 0, 0);

	/*
		Our second entry is our code segment. the base address is 0,
		limit is 4GB, uses 4KB granularity, uses 32-bit opcodes, and
		is a code segment descriptor.
	*/
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	/*
		The third entry is our Data Segment. It's EXACTLY the same
		as our code segment, but the descriptor type in this entry's
		access byte says it's a Data Segment.
	*/	
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	gdt_flush();
}
