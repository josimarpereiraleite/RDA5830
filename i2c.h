/*
	@File 		i2c.h
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		01/06/2021
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
	
*/

#ifndef I2C_H_
#define I2C_H_

void i2c_init(long CPU_FREQUENCY);

void i2c_start();

char i2c_ack();

char i2c_nack();

void i2c_write(char data);

void i2c_stop();

#endif /* I2C_H_ */