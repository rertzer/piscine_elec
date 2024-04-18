/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/18 13:25:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	uart_init();
	sei();
	while (true)
	{
	}
	return 0;
}

void	uart_init()
{
	// USART Baud Rate Register
	UBRR0 = (F_CPU + 8 * BAUDO) / 16 / BAUDO - 1;

	// USART transmitter, receiver and receiver interrupt enable
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);

}
void	uart_tx(char c)
{
	//waiting for transmit buffer to be empty
	while (! (UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}	

ISR(USART_RX_vect)
{
		char c = UDR0;
		if (c >= 'A' && c <= 'Z')
			c += 32;
		else if (c >= 'a' && c <= 'z')
			c -= 32;
		uart_tx(c);
}
