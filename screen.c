#include <screen.h>

void init_video() {
	texmemptr = (char*)0xB8000;
	position = 0;
	screenX = 0;
	screenY = 0;
	foreground = LIGHT_MAGENTA;
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
void putch(char c) {
	if(c == '\b') {
		//texmemptr[position] = ' ';
		//texmemptr[position+1] = colour;

		position -= 2;
		screenX--;
		if(screenX < 0) {
			screenX = 80;
			screenY--;
			if(screenY < 0) {
				screenX = 0;
				screenY = 0;
			}
		}
		if(position < 0) position = 0;
		texmemptr[position] = ' ';
		texmemptr[position+1] = colour;
		//moveCursor(position/2, 0);
		moveCursor(screenX, screenY);
		return;
	} else if(c == '\n') {
		int delta = 80-screenX;
		screenX = 0;
		screenY++;
		position += (delta*2);
		moveCursor(screenX, screenY);
		//moveCursor(position/2, screenY);
		return;
	}
	if(!isPrintable(c)) return;
	texmemptr[position] = c;
	texmemptr[position+1] = colour;
	position += 2;
	screenX++;
	if(screenX > 80) {
		screenY++;
		screenX = 0;
		//try to bullshit the position (it works!)
		position = 2*(screenY*80)+screenX;
	}
	//moveCursor(position/2, screenY);
	moveCursor(screenX, screenY);

	if(screenY > 25) {
		cls();
		//moveCursor(0,0);
	}
}
void puts(char* str) {
	int length = strlen(str);
	int i;
	for(i = 0; i < length; i++) {
		putch(str[i]);
	}
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
			putch(tmp-0xA+'a');
        } else {
            noZeroes = 0;
            putch(tmp+'0');
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA) {
        putch(tmp-0xA+'a');
    } else {
        putch(tmp+'0');
    }
}
void putdec(u32int n)
{

    if (n == 0)
    {
        putch('0');
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
		putch(' ');
	}
	position = 0;
	screenX = 0;
	screenY = 0;
	moveCursor(0, 0);
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
