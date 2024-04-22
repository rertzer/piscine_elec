/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eeprom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:39:06 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/22 14:24:40 by rertzer          ###   ########.fr       */
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

void	safe_eeprom_read(void *buffer, size_t offset, size_t length)
{
	char	*char_buffer = (char*)buffer;
	uint8_t magic = eeprom_read(offset);
	if (magic != MAGIC_SMALL_EEPROM)
		return;
	++offset;
	for (size_t i = 0; i < length; ++i)
	{
		char_buffer[i] = eeprom_read(offset + i);
	}
}

void	safe_eeprom_write(void *buffer, size_t offset, size_t length)
{
	char	*char_buffer = (char*)buffer;
	uint8_t	current = eeprom_read(offset);
	if (current == MAGIC_SMALL_EEPROM)
		return;
	eeprom_write(offset, MAGIC_SMALL_EEPROM);
	++offset;
	for (size_t i = 0; i < length; ++i)
	{
		current = eeprom_read(offset + i);
		if (char_buffer[i] != current)
			eeprom_write(offset + i, char_buffer[i]);
	}
}

