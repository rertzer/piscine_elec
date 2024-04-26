/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:34:28 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/24 10:38:30 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	uart_init()
{
	// USART Baud Rate Register
	UBRR0 = (F_CPU + 8 * BAUDO) / 16 / BAUDO - 1;

	// USART transmitter, receiver and receiver interrupt enable
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
}

char	uart_rx()
{
	//waiting for data
	while (! (UCSR0A & (1 << RXC0)));
	return UDR0;
}
void	uart_tx(char c)
{
	//waiting for transmit buffer to be empty
	while (! (UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

void	uart_printstr(char *str)
{
	while (*str != '\0')
	{
		uart_tx(*str);
		++str;
	}
}

void	uart_print_hex(uint8_t value)
{
	char	hex_nb[3];
	ft_itoa_hex(value, hex_nb);
	uart_printstr(hex_nb);
}

void	uart_print_dec(uint16_t value)
{
	char	dec_nb[6];
	ft_itoa_dec(value, dec_nb);
	uart_printstr(dec_nb);
}

ISR(USART_RX_vect)
{
	char c = UDR0;
	uart_tx(c);
}
