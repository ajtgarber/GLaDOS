#ifndef KB_H
#define KB_H

/* unsigned char kbdus[128] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8',
	'9', '0', '-', '=', '\b',
	'\t',
	'q', 'w', 'e', 'r',
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, // 29 - Control
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', //39
	'\'', '`', 0, //left shift
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', // 49
	'm', ',', '.', '/', 0, //right shift
	'*',
	0, // Alt
	' ', //Space bar
	0,  //Caps lock
	0, // 59 - F1 key ... > 
	0, 0, 0, 0, 0, 0, 0, 0,
	0, //F10
	0, //Scroll lock
	0, //Home key
	0, //Up Arrow
	0, //Page Up
	'-',
	0, //Left Arrow
	0,
	0, //Right Arrow
	'+',
	0, //79 - End key
	0, //Down key
	0, //Page Down
	0, //Insert
	0, //Delete
	0, 0, 0,
	0, // F11
	0, // F12
	0  //Everything else undefined
}; */

const char* lowerKeyMap = "\0\0121234567890-=\b\tqwertyuiop[]\n\0asdfghjkl;\'`\0\\zxcvbnm,./\0-\0 \0";
const char* upperKeyMap = "\0\0!@#$%^&*()_+\b\tQWERTYUIOP{}\n\0ASDFGHJKL:\"~\0|ZXCVBNM<>?\0*\0 \0";

char key_status = 0; //status for CONTROL, ALT, SHIFT, CAPS_LOCK
#define CONTROL_MASK   1
#define ALT_MASK       2
#define SHIFT_MASK     4
#define CAPS_LOCK_MASK 8

void keyboard_install();
void keyboard_handler(struct regs* r);

#endif
