/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/19 10:35:13 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	uart_init();

	while (1)
	{
		uart_tx('Z');
		_delay_ms(1000);
	}
	return 0;
}

void	uart_init()
{
	// USART Baud Rate Register
	UBRR0 = (F_CPU + 8 * BAUDO) / 16 / BAUDO - 1;

	// define async 8N1 
	//UCSR0C = 0b00000011;
	// USART transmitter enable
	UCSR0B |= (1 << TXEN0);
}

void	uart_tx(char c)
{
	//waiting for transmit buffer to be empty
	while (! (UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}	
