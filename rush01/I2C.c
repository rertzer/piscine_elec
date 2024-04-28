/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   I2C.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:42:06 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 14:37:34 by rertzer          ###   ########.fr       */
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
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (! (TWCR & (1<<TWINT)));
}

void	i2c_stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void	i2c_write(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (! (TWCR & (1<<TWINT)));
}

void	i2c_read()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (! (TWCR & (1<<TWINT)));
}

void	i2c_last_read()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (0<<TWEA);
	while (! (TWCR & (1<<TWINT)));
}
