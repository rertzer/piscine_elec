/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:23:59 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/22 17:58:58 by rertzer          ###   ########.fr       */
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
	for (; line[i] != '\0'; ++i)
	{
		if (line[i] != ' ')
			key[i] = line[i];
		else
		{
			++i;
			break;
		}
	}
	for (; line[i] != '\0'; ++i)
	{
		if (line[i] != ' ')
			value[i] = line[i];
		else
		{
			++i;
			break;
		}
	}




}
