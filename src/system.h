#ifndef __SYSTEM_H
#define __SYSTEM_H

/* main.c */
extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

/* screen.c */
extern void init_screen();
extern void settextattrib(unsigned char foreground_color, unsigned char background_color);
extern void cls();
extern void putch(unsigned char char_to_print);
extern void puts(unsigned char *text);
#endif