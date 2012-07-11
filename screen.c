#include <screen.h>

void init_video() {
	texmemptr = (char*)0xB8000;
	position = 0;
	screenX = 0;
	screenY = 0;
	foreground = LIGHT_GREEN;
	background = BLACK;
	updateColour();
	cls();
}
void updateColour() {
	colour = foreground | (background << 4);
}
void setBackground(int back) {
	background = back;
	updateColour();
}
void setForeground(int fore) {
	foreground = fore;
	updateColour();
}
void putch(char c, char updateCaret) {
	if(!isPrintable(c) && c != '\b' && c != '\n') return;
	if(c == '\b') {
		screenX--;
		if(screenX < 0) {
			screenX = 80;
			screenY--;
			if(screenY < 0) {
				screenX = 0;
				screenY = 0;
			}
		}
		texmemptr[position] = ' ';
		texmemptr[position+1] = colour;
	} else if(c == '\n') {
		int delta = 80-screenX;
		screenX = 0;
		screenY++;
	} else {
		texmemptr[position] = c;
		texmemptr[position+1] = colour;
		screenX++;
		if(screenX > 80) {
			screenY++;
			screenX = 0;
		}
	}
	if(screenY >= 25) {
		scroll();
	}
	//update the internal position
	position = 2*((screenY*80)+screenX);
	if(updateCaret)	
		moveCursor(screenX, screenY);
}
void puts(char* str) {
	int length = strlen(str);
	int i;
	for(i = 0; i < length; i++) {
		putch(str[i], 0);
	}
	moveCursor(screenX, screenY);
}
void puthex(u32int n) {
	s32int tmp;
	puts("0x");
	char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0) {
            continue;
        }
    
        if (tmp >= 0xA) {
            noZeroes = 0;
	    putch(tmp-0xA+'a', 1);
        } else {
            noZeroes = 0;
            putch(tmp+'0', 1);
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA) {
        putch(tmp-0xA+'a', 1);
    } else {
        putch(tmp+'0', 1);
    }
}
void putdec(u32int n)
{

    if (n == 0)
    {
        putch('0', 1);
        return;
    }

    s32int acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    puts(c2);

}
void cls() {
	position = 0;
	int i;
	for(i = 0; i < 80*25; i++) {
		putch(' ', 0);
	}
	position = 0;
	screenX = 0;
	screenY = 0;
	//moveCursor(0, 0);
}
void moveCursor(int x, int y) {
	unsigned temp;
	temp = (y * 80) + x;

	/* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
	outb(0x3d4, 14);
	outb(0x3d5, temp >> 8);
	outb(0x3d4, 15);
	outb(0x3d5, temp);
}
char isPrintable(char c) {
	if(c == '\n') return 1;
	if(c < 32 || c == 127) return 0;
	return 1;
}
void scroll() {
	//Row 25 is the end, this means we need to scroll up
	if(screenY >= 25) {
		//Move the current text chunk that makes up the screen
		//back in the buffer by a line
		int i;
		for(i = 0*80; i < 48*80; i++) {
			texmemptr[i] = texmemptr[i+160];
		}

		//The last line should now be blank. Do this by writing
		//80 spaces to it;
		for(i = 48*80; i < 50*80; i++) {
			if(i % 2 == 0) {
				texmemptr[i] = ' ';
			} else {
				texmemptr[i] = colour;
			}		
		}
		//The cursor should now be on the last line.
		screenY = 24;
		screenX = 0;
		moveCursor(screenX, screenY);
	}
}
