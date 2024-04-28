/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:40:12 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 17:25:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	readline(uint8_t* buffer)
{
	int i = 0;
	while (i < 254)
	{
		unsigned char c = uart_rx();
		//backspace
		if (c == 127)
		{
			if (i != 0)
			{
				buffer[i] = '\0';
				--i;
			}
		uart_tx(8);
		uart_tx(32);
		uart_tx(8);
		}
		//cariage return
		else if (c == 13)
		{
			break;
		}
		else
		{
			buffer[i] = c;
			++i;
		}
		uart_tx(c);
	}
	buffer[i] = '\0';
}
