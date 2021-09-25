/*
	@File 		i2c.cpp
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		01/06/2021
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
	
*/

#include <avr/io.h>

#define PRESCALER				8
#define SCL_FREQUENCY			100000

void i2c_init(long CPU_FREQUENCY)											
{
	long bitrate = ((CPU_FREQUENCY / SCL_FREQUENCY) - 16) / PRESCALER;
	
	TWBR = bitrate;
	TWSR &= (~((1<<TWPS1)|(1<<TWPS0)));
}

void i2c_start()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void i2c_write(char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

char i2c_ack()	
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);					
	while (!(TWCR & (1<<TWINT)));							
	return TWDR;
}

char i2c_nack()
{
	TWCR=(1<<TWEN)|(1<<TWINT);								
	while (!(TWCR & (1<<TWINT)));						
	return TWDR;
}

void i2c_stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(TWCR & (1<<TWSTO));
}
