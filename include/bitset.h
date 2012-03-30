#include <common.h>

#ifndef BITSET_H
#define BITSET_H

u32int *frames;
u32int nframes;

extern u32int placement_address; //defined in kheap.c

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

static void set_frame(u32int frame_addr) {
	u32int frame = frame_addr/0x1000;
	u32int idx = INDEX_FROM_BIT(frame);
	u32int off = OFFSET_FROM_BIT(frame);
	frames[idx] |= (0x1 << off);
}

static void clear_frame(u32int frame_addr) {
	u32int frame = frame_addr/0x1000;
	u32int idx = INDEX_FROM_BIT(frame);
	u32int off = OFFSET_FROM_BIT(frame);
	frames[idx] &= ~(0x1 << off);
}

static u32int test_frame(u32int frame_addr) {
	u32int frame = frame_addr/0x1000;
	u32int idx = INDEX_FROM_BIT(frame);
	u32int off = OFFSET_FROM_BIT(frame);
	return (frames[idx] & (0x1 << off));
}

static u32int first_frame() {
	u32int i, j;
	for(i = 0; i < INDEX_FROM_BIT(nframes); i++) {
		if(frames[i] != 0xFFFFFFFF) {
			for(j = 0; j < 32; j++) {
				u32int toTest = 0x1 << j;
				if( !(frames[i] & toTest) ) {
					return i*4*8+j;
				}
			}
		}
	}
}

void alloc_frame(page_t *page);

void free_frame(page_t* page);

#endif
