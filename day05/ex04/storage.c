/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:23:59 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/23 10:36:36 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	doCommand()
{
	char			line[256];
	char			command[256];
	char			key[256];
	char			value[256];
	enum command	com = INVALID;

	uart_readline((char*)line);
	uint16_t i = 0
	for (; line[i] != '\0'; ++i)
	{
		if (line[i] != ' ')
			command[i] = line[i];
		else
		{
			++i;
			break;
		}
	}
	command[i] = '\0';
	while (line[i] != '"' && line != '\0')
		++i;
	if (line[i] == '"')
		++i;
	for (; line[i] != '\0'; ++i)
	{
		if (line[i] != '"')
			key[i] = line[i];
		else
		{
			++i;
			break;
		}
	}
	key[i] = '\0';
	while (line[i] != '"' && line != '\0')
		++i;
	if (line[i] == '"')
		++i;

	for (; line[i] != '\0'; ++i)
	{
		if (line[i] != '"')
			value[i] = line[i];
		else
		{
			++i;
			break;
		}
	}
	value[i] = '\0';
	if (! ft_strcmp(command, "READ"))
		storage_read(key);
	else if (! ft_strcmp(command, "WRITE"))
		storage_write(key, value);
	else if (! ft_strcmp(command, "FORGET"))
		storage_forget(key);
	else
		storage_invalid();
}

void	storage_read(char *key)
{
	uint16_t	id = storage_get_id_by_key(key);
	if (id == 0)
		return storage_key_not_found();
	storage_read_value_by_id(id);
}

void	storage_write(char *key, char *value)
{
	uint16_t	id = storage_get_id_by_key(key);
	if (id == 0)
		return storage_key_not_found();
	storage_store_key(key);
	storage_store_value(value);
}

void	storage_forget(char *key)
{
	uint16_t	id = storage_get_id_by_key(key);
	if (id == 0)
		return storage_key_not_found();
	storage_forget_by_id(id);
}

void	storage_invalid()
{
	uart_printstr("Invalid command\r\n");
}

uint16_t	storage_get_id_by_key(char *key)
{
	uint16_t	address = 0x01;
	uint16_t	id;
	uint16_t	size;
	char		content[256];
	while (address < 1020)
	{
		eeprom_buffer_read((void*)&id, address, 2);
		if (id & 0xF0 == KEY)
		{
			eeprom_buffer_read((void*)&size, address + 2, 2);
			eeprom_buffer_read((void*)&content, address + 4, size);
			if (! ft_strcmp(content, key))
			{
				eeprom_buffer_read((void*)&address, address , 2);
			
			}
		}
		address = eeprom_find_next_address(address);
	}
}

void	storage_key_not_found()
{
	uart_printstr("Not found\r\n");
}



void	storage_read_value_by_id(uint16_t id)
{
}
