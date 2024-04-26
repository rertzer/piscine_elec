/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   I2C.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:42:06 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/26 14:10:27 by rertzer          ###   ########.fr       */
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
	//TWCR |= (1 << TWIE); 
}

void	i2c_start()
{
		//send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	
	// wait for TWINT flag st, indicating that the START condition has been transmitted
	while (! (TWCR & (1<<TWINT)));
	uart_printstr("start\r\n");
	display_status(TWSR);
}

void	i2c_stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	display_status(TWSR);
}

void	i2c_write(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (! (TWCR & (1<<TWINT)));
	uart_printstr("write\r\n");
	display_status(TWSR);	
}

void	i2c_read()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (! (TWCR & (1<<TWINT)));
	uart_printstr("read\r\n");
	display_status(TWSR);
}

void	i2c_last_read()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (0<<TWEA);
	while (! (TWCR & (1<<TWINT)));
	uart_printstr("read\r\n");
	display_status(TWSR);
}
