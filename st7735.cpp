/*
 * st7735.cpp
 *
 * Created: 03/09/2021 15:50:50
 *  Author: Desktop
 */ 

#include "st7735.h"

#include <avr/io.h>
#include <avr/pgmspace.h>

unsigned char ST7735_BUFFER[32] = { 0 };

void Write(unsigned char data)
{
	for (int i=7; i>=0; i--)
	{
		ST7735_CLK_HIGH;
		
		if (data & (1 << i))
		ST7735_MOSI_HIGH;
		else
		ST7735_MOSI_LOW;
		
		ST7735_CLK_LOW;
	}
}

void ST7735::Command(unsigned char cmd)
{
	ST7735_DC_LOW;
	ST7735_CS_LOW;

	Write(cmd);
	
	ST7735_CS_HIGH;
}

void ST7735::Write_8bits(unsigned char data)
{
	ST7735_DC_HIGH;
	ST7735_CS_LOW;
	
	Write( data );
	
	ST7735_CS_HIGH;
}

void ST7735::Write_16bits(unsigned int data)
{
	ST7735_DC_HIGH;
	ST7735_CS_LOW;
	
	Write( (unsigned char) (data >> 8) );
	Write( (unsigned char) (data & 0xFF) );
	
	ST7735_CS_HIGH;
}

void ST7735::Set_Window(int xs, int xe, int ys, int ye)
{
	ST7735::Command(CASET);
	ST7735::Write_16bits(xs);
	ST7735::Write_16bits(xe);
	
	ST7735::Command(RASET);
	ST7735::Write_16bits(ys);
	ST7735::Write_16bits(ye);
	
	ST7735::Command(RAMWR);
}

void ST7735::Set_Pixel(int x, int y, int color)
{
	ST7735::Set_Window(x, x+1, y, y+1);
	
	ST7735::Write_16bits(color);
	ST7735::Write_16bits(color);
}


void ST7735::Draw_Image_16bits(const unsigned char *ImageBuffer, char X, char Y, char IMAGE_W, char IMAGE_H)
{
	ST7735::Set_Window(X, X+IMAGE_W-1, Y, Y+IMAGE_H-1);
	
	for (int i=0; i<(IMAGE_W*IMAGE_H)*2; i++)
	{
		ST7735::Write_8bits(pgm_read_byte(&ImageBuffer[i]));
	}
}

void ST7735::Clear(unsigned int x, unsigned int y, unsigned int size_W, unsigned int size_H, unsigned int color)
{
	ST7735::Set_Window(x, x+size_W-1, y, y+size_H-1);
	
	for (unsigned int i=0; i<(size_W*size_H)*2; i++)
	{
		ST7735::Write_16bits(color);
	}
}

void ST7735::Rotation(unsigned char Rot)
{
	ST7735::Command(0x36);
	Write_8bits(Rot << 5);
}

void ST7735::Fill(int x, int y, int width, int height, unsigned int color)
{
	ST7735::Set_Window(x, x+width, y, y+height);
	
	for (unsigned char h=0; h<width; h++)
	{
		for (unsigned char w=0; w<height; w++)
		{
			ST7735::Write_16bits(color);
		}
	}
}


// EX: DrawRectangle(5, 5, 50, 16, ST7735_COLOR_BLUE);
void ST7735::DrawRectangle(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned int color)
{
	unsigned char k = 0;
	unsigned char i = 0;
	
	for(i=0; i<height; i++){
		for(k=0; k<width; k++){
			if( i%(height-1) == 0){
				Set_Pixel(x + k, y + i, color);
			}
			// -- //
			if( k%(width-1) == 0){
				Set_Pixel(x + k, y + i, color);
			}
		}
	}
}

void ST7735::DrawRectangle_2(unsigned char x, unsigned char y, unsigned char area, unsigned int color)
{
	for(unsigned char i=0; i<(area + 1); i++)
	{
		Set_Pixel(x, y + i, color);
		Set_Pixel(x + i, y, color);
		Set_Pixel(x + i, y + area, color);
		Set_Pixel(x + area + 1, y + i, color);
	}
}

/*
*
*	Draw_8Bits(Speaker_On, 130, 5, 9, 1, ST7735_COLOR_LIGHT_GRAY);
*/

void ST7735::Draw_Pixel_Image(
const unsigned char *Buffer,
unsigned char x, unsigned char y,
unsigned char w, unsigned char Pixels, unsigned int Color)
{
	unsigned char j = 0;
	unsigned char Data = 0;
	unsigned char col = 0;
	
	for (unsigned char i=0; i<Pixels; i++)
	{
		for (; col<w; col++)
		{
			Data = pgm_read_byte(&Buffer[col]);
			
			for (unsigned char r=0; r<8; r++)
			{
				if (Data & (1 << r))
				{
					Command(CASET);
					Write_16bits(x + col);
					Write_16bits(w);
					
					Command(RASET);
					Write_16bits(y + r);
					Write_16bits(Pixels);
					
					Command(RAMWR);
					
					Write_16bits( Color );
				}
			}
		}
		
		y += 8;
		x -= w;
		j += w;
	}
}

void ST7735::WriteChar(unsigned char data, unsigned int x, unsigned int y, const unsigned char Font[], unsigned int Color)
{
	unsigned char width				= pgm_read_byte( &Font[0] );	// font width
	unsigned char page				= pgm_read_byte( &Font[2] );	// font pages
	unsigned char st				= pgm_read_byte( &Font[3] );	// font start
	unsigned char ch				= 0;							// character
	unsigned char fh				= 5;							// font file header size
	unsigned int col				= 0;							// col
	unsigned int i					= 0;							// width * width ...
	unsigned int row				= 0;							// rows
	unsigned int j					= 0;
	
	int id = ( ( ( data - st) * ( (width+1) * 2) + fh ) );

	for (i=0; i<page; i++)
	{
		for (; col < (width + j); col++)
		{
			ch = pgm_read_byte( &Font[ (id + col) + 2 ] );
			
			for(row=0; row<8; row++)
			{
				if (ch & (1 << row))
				{
					Command(CASET);
					Write_16bits(x + col);
					Write_16bits(1);
					
					Command(RASET);
					Write_16bits(y + row);
					Write_16bits(1);
					
					Command(RAMWR);
					
					Write_16bits( Color );
				}
			}
		}
		
		y += 8;
		x -= width;
		j += width;
	}
}

void ST7735::WriteString(const char *data, unsigned int x, unsigned int y, const unsigned char Font[], unsigned int Color)
{
	while(*data)
	{
		WriteChar(*data, x, y, Font, Color);
		
		unsigned char width				= pgm_read_byte( &Font[0] );	// font width
		unsigned char st				= pgm_read_byte( &Font[3] );	// font start
		unsigned char fh				= 5;							// font file header size
		int i							= ( ( ( *data++ - st) * ( (width+1) * 2) + fh ) );
		
		x								+= pgm_read_byte( &Font[ i ] ) + 1;
	}
}

void ST7735::Init()
{
	DDRD |= (1 << ST7735_CS);
	DDRD |= (1 << ST7735_DC);
	DDRD |= (1 << ST7735_RS);
	DDRB |= (1 << ST7735_MOSI);
	DDRB |= (1 << ST7735_CLK);
	
	ST7735_CS_HIGH;
	ST7735_RS_HIGH;
	
	ST7735::Command(0x11); // sleep out
	
	// MADCTL: 0x36
	ST7735::Command(0x36);
	ST7735::Write_8bits(0);
	
	// COLMOD: 0x3A
	ST7735::Command(0x3A);
	ST7735::Write_8bits(0x05);
	
	ST7735::Command(0x29); // display on
	
}


//##########################################################

