#include <system.h>
#include <kb.h>

void keyboard_install() {
	key_status = 0;
	irq_install_handler(1, keyboard_handler);
}

void keyboard_handler(struct regs* r) {
	unsigned char scancode;

	scancode = inb(0x60); //read from keyboard data buffer

	if(scancode & 0x80) {
		//key released
		if(scancode == 0xAA) key_status -= SHIFT_MASK; //potentially dangerous
	} else {
		//key pressed
		if(scancode == 0x2A) key_status |= SHIFT_MASK;

		if(key_status & SHIFT_MASK)
			putch(upperKeyMap[scancode], 0);
		else
			putch(lowerKeyMap[scancode], 0);
	}
}
