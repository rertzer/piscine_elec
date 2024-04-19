/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   I2C.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:42:06 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/19 18:15:09 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"


void	i2c_init()
{
	// set frequency
	// freq = F_CPU / (16 + 2 . TWBR . Prescale)
	TWBR = 72;
	
	// prescaler at 1
	TWSR &= ~(1<<TWPS1 | 1<<TWPS0);
	
	//Interrupt Enable
	TWCR |= (1 << TWIE); 
}

void	i2c_start()
{
	// AHT20  address
	//TWAR = 0x38;
	
	//send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	
	// wait for TWINT flag st, indicating that the START condition has been transmitted
	while (! (TWCR & (1<<TWINT)));
	uart_printstr("start\r\n");
	display_status(TWSR);
	//TWCR &= ~(1<<TWSTA);
	// check value of TWI Status Register
//	if ((TWSR &  0xF8) != START)
//		ERROR();
}

void	i2c_stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	display_status(TWSR);
}

void	i2c_write(unsigned char data)
{
	TWDR = (0x38 << 1);
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (! (TWCR & (1<<TWINT)));
	uart_printstr("write\r\n");
	display_status(TWSR);
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (! (TWCR & (1<<TWINT)));
	display_status(TWSR);
}

char	i2c_read()
{
	TWDR = (0x38 << 1) | 1;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (! (TWCR & (1<<TWINT)));
	uart_printstr("read\r\n");
	display_status(TWSR);
	char data = TWDR;
	return data;
}


