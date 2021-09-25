/*
	@File 		main.cpp
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		07/06/2021
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "i2c.h"

#define RDA5830_ADDRESS_WRITE							0x22 // write
#define RDA5830_ADDRESS_READ							0x23 // READ

void nop(){
	for (int i=0; i<6553; i++){
		asm("nop");
	}
}

void RDA5830_WRITE(unsigned char reg, unsigned short data)
{
	i2c_start();
	
	i2c_write(RDA5830_ADDRESS_WRITE);
	
	// REGISTER
	i2c_write(reg);
	
	// DATA HIGHT BYTE
	i2c_write( data >> 8 );
	
	// DATA LOW BYTE
	i2c_write( data );
	
	i2c_stop();
	
	nop();	
}

unsigned short STATION[] = {895, 901, 919, 949, 957, 971, 983, 995, 1021, 1029, 1043, 1067, 1073};

unsigned int i = 0;

unsigned int Channel = 0;

int main(void)
{
	_delay_ms(100);

	i2c_init(F_CPU);
	
	//	GOIANIA (GOIÁS) BRAZIL STATIONS
	//	895		-	PAZ FM						-	89.5
	//	901		-	RADIO BRASIL CENTRAL		-	90.1
	//	919		-	VINHA FM					-	91.9
	//	949		-	INTERATIVA					-	94.9
	//	957		-	CLUBE FM					-	95.7
	//	971		-	CBN							-	97.1
	//	983		-	RADIO SUCESSO				-	98.3
	//	995		-	RADIO 99					-	99.5
	//	1021	-	RADIO ALPHA					-	102.1
	//	1029	-	RADIO ROCK					-	102.9
	//	1043	-	TERRA FM					-	104.3
	//	1067	-	JOVEM PAN					-	106.7
	//	1073	-	107 FM						-	107.3
	
	Channel = STATION[ i ];
	Channel = (Channel - 870);
	Channel = (Channel << 6) | 0x0010;
	
	// INIT
	RDA5830_WRITE( 0x02, 0xD001); 
	RDA5830_WRITE( 0x04, 0x0000);
	RDA5830_WRITE( 0x05, 0x88AF); 
	
	RDA5830_WRITE( 0x03, Channel);
	
	DDRB &=~(1 << PB0);
	
	PORTB = (1 << PB0);

    while(1)
	{
 		if (!(PINB & (1 << PB0)))
 		{
 			i++;
 			
 			i = (i > 12) ? 0 : i;
 			
 			Channel = STATION[i];
 			Channel = (Channel - 870);
 			Channel = (Channel << 6) | 0x0010;
 			
 			RDA5830_WRITE( 0x03, Channel);
 			
 			_delay_ms(250);
 		}
	}
}
