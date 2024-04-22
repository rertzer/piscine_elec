/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   I2C.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:42:06 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/22 09:16:04 by rertzer          ###   ########.fr       */
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
}

void	i2c_start()
{
	// AHT20  address
	TWAR = 0x38;
	
	//send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	
	// wait for TWINT flag set,
	// indicating that the START condition has been transmitted
	while (! (TWCR & (1<<TWINT)));
	display_status(TWSR);	
	// check value of TWI Status Register
//	if ((TWSR &  0xF8) != START)
//		ERROR();
}

void	i2c_stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	display_status(TWSR);
}

