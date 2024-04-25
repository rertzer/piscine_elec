/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:40:12 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/23 14:11:20 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	read_line(char* buffer)
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

void	uart_init()
{
	// USART Baud Rate Register
	UBRR0 = (F_CPU + 8 * BAUDO) / 16 / BAUDO - 1;

	// USART transmitter, receiver enable
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

}

void	uart_tx(char c)
{
	//waiting for transmit buffer to be empty
	while (! (UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}	

char	uart_rx()
{
	//waiting for data
	while (! (UCSR0A & (1 << RXC0)));
	return UDR0;
}	

void	uart_print(char *str)
{
	while (*str != '\0')
	{
		uart_tx(*str);
		++str;
	}
}
