#include <system.h>
#include <screen.h>


//points to the text memory of the screen
unsigned short *screen_textmem_ptr;

//height and width of screen
int screen_height, screen_width;

/*attributes like foreground and background colors
top 4 bits are background color and bottom 4 bits
are foreground color
*/
char text_attrib;

//cursor positions
int cursor_x, cursor_y;

//unsigned short representing a blank character
unsigned blank;


//tab space
int tab_space=8;

//---------------------------------methods-----------------------------------
void init_screen(void) {
	screen_textmem_ptr	=	(unsigned short *)0xB8000;
	text_attrib			=	WHITE;
	screen_height		=	25;
	screen_width		=	80;
	blank				=	0x20 | (text_attrib<<8);
	cls();
}

void cls() {
	memsetw(screen_textmem_ptr, blank, screen_width*screen_height);
	cursor_x			=	0;
	cursor_y			=	0;	
}

void move_cursor(void) {
	unsigned cursor_position;
	/*
		we need to store the index of the cursor in E and F registers of VGA-registers
		E and F are 7 bit registers and E is 'Cursor Location High' and F is 'Cursor 
		Location Low'
	*/
	cursor_position = (cursor_y * screen_width) + cursor_x;
	
	outportb(0x3D4, 0xE);
	outportb(0x3D5, cursor_position >> 8);
	outportb(0x3D4, 0xF);
	outportb(0x3D5, cursor_position);
}

void scroll(void) {
	if (cursor_y >= screen_height) {
		int temp = cursor_y - screen_height + 1;
		memcpy((unsigned char *)screen_textmem_ptr, (const unsigned char *)screen_textmem_ptr+(screen_width*temp), (screen_height-temp)*screen_width*2);
		memsetw(screen_textmem_ptr+((screen_height-temp)*screen_width), blank, screen_width);
		cursor_y = screen_height - 1; 
	}
}

void putch(unsigned char char_to_print) {
	unsigned short *where_to_print;
	
	// handle '\b'
	if (char_to_print == '\b') {
		if (cursor_x == 0) {
			cursor_x = screen_width;
			cursor_y--;
		}
		else {
			cursor_x--;
		}
	}
	// handle '\t'
	else if (char_to_print == '\t') {
		cursor_x = (cursor_x + tab_space) & (tab_space-1);
	}
	// handle '\r'
	else if (char_to_print == '\r') {
		cursor_x = 0;
	}
	// handle '\n'
	else if (char_to_print == '\n') {
		cursor_y++;
		cursor_x=0;
	}
	else if (char_to_print >= ' ') {
		where_to_print = screen_textmem_ptr + ((cursor_y * screen_width) + cursor_x);
		*where_to_print = ((text_attrib << 8) | char_to_print);
		cursor_x++;
	}
	
	// If the cursor reached end of the line, make the cursor go to next line
	if (cursor_x >= screen_width) {
		cursor_x = 0;
		cursor_y++;
	}
	
	//scroll the screen if needed and finally move the cursor
	scroll();
	move_cursor();
}

void puts(unsigned char *text) {
	int len_of_str = strlen((const char *)text);
	int temp;
	for(temp=1; temp<=len_of_str; temp++) {
		putch(text[temp]);
	}
}

void settextattrib(unsigned char foreground_color, unsigned char background_color) {
	text_attrib = background_color << 4 | (foreground_color & 0x0F);
}