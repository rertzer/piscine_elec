/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eeprom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:39:06 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/22 10:55:11 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

unsigned char eeprom_read(unsigned int address)
{
	cli();
	/* Wait for completion of previous write */
	while (EECR & (1<<EEPE));

	/* Set up address register */
	EEAR = address;

	/* read enable */
	EECR |= (1<<EERE);

	/* Return data from Data Register */
	return EEDR;
	sei();
}

void eeprom_write(unsigned int address, unsigned char data)
{
	cli();
	/* Wait for completion of previous write */
	while (EECR & (1<<EEPE));

	/* Set up address and Data Registers */
	EEAR = address;
	EEDR = data;

	/* master write enable  */
	EECR |= (1<<EEMPE);

	/* write enable */
	EECR |= (1<<EEPE);
	sei();
}
