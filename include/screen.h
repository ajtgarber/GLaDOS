#include <common.h>

#ifndef SCREEN_H
#define SCREEN_H

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define LIGHT_BROWN 14
#define WHITE 15

char* texmemptr;
int position; //used for setting memory addresses
int screenX;
int screenY; //more "friendly" locations
int foreground;
int background;
int colour;

char isPrintable(char c);

void init_video();
void cls();
void putch(char c, char updateCursor);
void puts(char* str);
void puthex(u32int n);
void putdec(u32int n);
void setBackground(int background);
void setForeground(int foreground);
void updateColour();
void moveCursor(int x, int y);
void scroll();

#endif
