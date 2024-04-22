/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eeprom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:39:06 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/22 17:42:20 by rertzer          ###   ########.fr       */
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

bool	eepromalloc_init(uint16_t length)
{
	if (length < 5)
		return false;
	uint16_t	empty_block[2];
	empty_block[0] = 0x00;
	empty_block[1] = length - 5;
	return safe_eeprom_write(0x00, empty_block, 4);
}

bool	eepromalloc_write(uint16_t id, void *buffer, uint16_t length)
{
	uint16_t	address = eeprom_find_id(id);
	if (address == 0x00)
	{
		return eepromalloc_newrite(id, buffer, length);
	}
	else
	{
		return eepromalloc_rewrite(address, buffer, length);
	}
}

bool	eepromalloc_newrite(uint16_t id, void *buffer, uint16_t length)
{
	uint16_t	address = eeprom_find_empty(length);
	uint16_t	total_size;
	if (!(address != 0x00 &&
		eeprom_buffer_read((void *)&total_size, address + 2, 2)))
		return false;
	if (total_size - length > 4)
	{
		if(! eeprom_write_empty_slot(address + 4 + length, total_size - (4 + length)))
			return false;
		total_size = length;
	}
	if (!(eeprom_buffer_write((void*)&id, address, 2) &&
		eeprom_buffer_write((void*)&total_size, address + 2, 2) &&
		eeprom_buffer_write(buffer, address + 4, length)))
		return false;
	return true;
}

bool	eepromalloc_rewrite(uint16_t address, void *buffer, uint16_t length)
{
	uint16_t value;
	if (eeprom_buffer_read((void*)&value, address + 2, 2) == false)
		return false;
	if (length > value)
		return false;
	return eeprom_buffer_write(buffer, address + 4, length);
}

bool	eepromalloc_read(uint16_t id, void *buffer, uint16_t length)
{
	uint16_t	address = eeprom_find_id(id);
	if (address == 0x00)
		return false;
	return eeprom_buffer_read(buffer, address + 4, length);
}

bool	eepromalloc_free(uint16_t id)
{
	uint16_t	address = eeprom_find_id(id);
	if (address == 0x00)
		return false;
	id = 0;
	eeprom_buffer_write((void*)&id, address, 2);
	return true;
}

uint16_t	eeprom_find_id(uint16_t id)
{
	uint16_t	address = 0x01;
	while (address < 1020)
	{
		uint16_t	value = 0;
		if (eeprom_buffer_read((void*)&value, address, 2) == false)
			break;
		if (value == id)
			return address;
		if (eeprom_buffer_read((void*)&value, address + 2, 2) == false)
			break;
		address += value + 4;
	}
	return 0x00;
}

uint16_t	eeprom_find_empty(uint16_t length)
{
	uint16_t	address = 0x01;
	while (address < 1020)
	{
		uint16_t	current_id = 0;
		uint16_t	current_length = 0;
		if (eeprom_buffer_read((void*)&current_id, address, 2) == false)
			break;
		if (eeprom_buffer_read((void*)&current_length, address + 2, 2) == false)
			break;
		if (current_id == 0 && current_length <= length)
			return address;
		address += value + 4;
	}
	return 0x00;
}

bool	eeprom_buffer_read(void *buffer, uint16_t offset, uint16_t length)
{
	char	*char_buffer = (char*)buffer;
	if (length < 1 || length > 1023)
		return false;
	for (uint16_t i = 0; i < length; ++i)
	{
		buffer[i] = eeprom_read(offset + i);
	}
	return true;
}

bool	eeprom_buffer_write(void *buffer, uint16_t offset, uint16_t length)
{
	char	*char_buffer = (char*)buffer;
	if (offset < 1 || offset + length > 1023)
		return false;
	for (uint16_t i = 0; i < length; ++i)
	{
		eeprom_write(offset + i, buffer[i]);
	}
	return true;
}

bool	safe_eeprom_write(void *buffer, uint16_t offset, uint16_t length)
{
	char	*char_buffer = (char*)buffer;
	uint8_t	current = eeprom_read(offset);
	if (current == MAGIC_EEPROM)
		return false;
	eeprom_write(offset, MAGIC_EEPROM);
	++offset;
	for (uint16_t i = 0; i < length; ++i)
	{
		current = eeprom_read(offset + i);
		if (char_buffer[i] != current)
			eeprom_write(offset + i, char_buffer[i]);
	}
	return true;
}
