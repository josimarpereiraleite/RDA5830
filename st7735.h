/*
 * st7735.h
 *
 * Created: 03/09/2021 15:50:41
 *  Author: Desktop
 */ 


#ifndef ST7735_H_
#define ST7735_H_

//---------------------------------
#include "Fonts/Arial_12x12.h"
#include "Fonts/Arial_13x13.h"
#include "Fonts/Arial_16x16.h"
#include "Fonts/Arial_Bold_10x11.h"
#include "Fonts/Arial_Bold_16x17.h"
#include "Fonts/Arial_Italic_11x12.h"

#include "Fonts/Ms_Serif.h"
#include "Fonts/Verdana_11x11.h"
#include "Fonts/Calibri_9x10.h"
#include "Fonts/Tahoma_10x11.h"
#include "Fonts/Times_New_Roman_11x12.h"
#include "Fonts/Times_New_Roman_Bold_12x11.h"

#define ST7735_CS						PD7
#define ST7735_DC						PD6
#define ST7735_RS						PD5

#define ST7735_MOSI						PB3
#define ST7735_CLK						PB5

#define ST7735_RS_LOW					PORTD &= (unsigned char)~(1<<ST7735_RS)
#define ST7735_RS_HIGH					PORTD |= (1<<ST7735_RS)

#define ST7735_CS_LOW					PORTD &= (unsigned char)~(1<<ST7735_CS)
#define ST7735_CS_HIGH					PORTD |= (1<<ST7735_CS)

#define ST7735_DC_LOW					PORTD &= (unsigned char)~(1<<ST7735_DC)
#define ST7735_DC_HIGH					PORTD |= (1<<ST7735_DC)


#define ST7735_CLK_LOW					PORTB &= (unsigned char)~(1<<ST7735_CLK)
#define ST7735_CLK_HIGH					PORTB |= (1<<ST7735_CLK)

#define ST7735_MOSI_LOW					PORTB &= (unsigned char)~(1<<ST7735_MOSI)
#define ST7735_MOSI_HIGH				PORTB |= (1<<ST7735_MOSI)

#define CASET							0x2A	// Column Address Set
#define RASET							0x2B	// Row Address Set
#define RAMWR							0x2C	// Memory write


// ST7735 COLORS 565
#define RGB(r,g,b)						(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

// ST7735 COLOR_RGB
#define ST7735_COLOR_RED				RGB(255,0,0)
#define ST7735_COLOR_YELLOW				RGB(255,255,0)
#define ST7735_COLOR_BLACK				RGB(0,0,0)
#define ST7735_COLOR_WHITE				RGB(255,255,255)
#define ST7735_COLOR_ORANGE				RGB(255,165,0)
#define ST7735_COLOR_BLUE				RGB(0,0,255)
#define	ST7735_COLOR_AQUA				RGB(0,255,255)
#define ST7735_COLOR_LIGHT_GRAY			RGB(211,211,211)
#define ST7735_COLOR_LIME				RGB(0,255,0)
#define ST7735_COLOR_GAINSBORO			RGB(220,220,220)
#define ST7735_COLOR_SILER				RGB(192,192,192)
#define ST7735_COLOR_GREEN				RGB(0,128,0)
#define ST7735_COLOR_NAVY				RGB(0,0,128)
#define ST7735_COLOR_GRAY				RGB(128,128,128)
#define ST7735_COLOR_STATE_GRAY			RGB(112,128,144)
#define ST7735_COLOR_DIM_GRAY			RGB(105,105,105)
#define ST7735_COLOR_MARRON				RGB(128,0,0)
#define ST7735_COLOR_GOLDEN_ROD			RGB(218,165,32)
#define ST7735_COLOR_DARK_ORANGE		RGB(255,140,0)
#define ST7735_COLOR_PALE_GOLDEN_ROD	RGB(238,232,170)
#define ST7735_COLOR_KHAKI				RGB(240,230,140)
#define ST7735_COLOR_OLIVE				RGB(128,128,0)
#define ST7735_COLOR_YELLOW_GREEN		RGB(154,205,50)
#define ST7735_COLOR_SKY_BLUE			RGB(135,206,235)
#define ST7735_COLOR_TEAL				RGB(0,128,128)
#define ST7735_COLOR_BISQUE				RGB(255,228,196)
#define ST7735_COLOR_BEIGE				RGB(245,245,220)
#define ST7735_COLOR_WHEAT				RGB(245,222,179)
#define ST7735_COLOR_STATE_GRAY			RGB(112,128,144)
#define ST7735_COLOR_DIM_GRAY			RGB(105,105,105)
#define ST7735_COLOR_DARK_GRAY			RGB(169,169,169)
#define ST7735_COLOR_WHITE_SMOKE		RGB(245,245,245)


// ST7735 FONTS LIBRARY
#define ST7735_FONT_TIMES_NEW_ROMAN_REGULAR_8 		0
#define ST7735_FONT_ARIAL_REGULAR_8 				1
#define ST7735_FONT_ARIAL_BOLD_8					2
#define ST7735_FONT_TIMES_NEW_ROMAN_BOLD_8	 		5			
#define ST7735_FONT_ARIAL_REGULAR_12 				6
#define ST7735_FONT_CALIBRI_REGULAR_8 				7
#define ST7735_FONT_CALIBRI_BOLD_8 					8
#define ST7735_FONT_ARIAL_BOLD_12 					9

class ST7735
{
	public:
	
	// SYSTEM
	void Command(unsigned char cmd);
	void Set_Window(int xs, int xe, int ys, int ye);
	void Set_Pixel(int x, int y, int color);
	void Write_8bits(unsigned char data);
	void Write_16bits(unsigned int data);
	
	// DRAW PICTURE
	void Draw_Image_16bits(const unsigned char *ImageBuffer, char X, char Y, char IMAGE_W, char IMAGE_H);
	void Draw_Pixel_Image(const unsigned char *Buffer,unsigned char x, unsigned char y,unsigned char w, unsigned char Pixels, unsigned int Color);
	
	// Draw Rectangle
	void DrawRectangle(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned int color);
	void DrawRectangle_2(unsigned char x, unsigned char y, unsigned char area, unsigned int color);
	
	// CLEAR DISPLAY OR FILL COLOR
	void Clear(unsigned int x, unsigned int y, unsigned int size_W, unsigned int size_H, unsigned int color);
	
	// INIT
	void Init();
	
	// STRINGS
	void WriteChar(unsigned char c, unsigned int x, unsigned int y, const unsigned char Font[], unsigned int Color);
	void WriteString(const char *s, unsigned int x, unsigned int y, const unsigned char Font[], unsigned int Color);
	void Fill(int x, int y, int width, int height, unsigned int color);
	
	//DISPLAY ROTATION
	void Rotation(unsigned char Rot);
	
	unsigned int X;
	unsigned int Y;
};


#endif /* ST7735_H_ */