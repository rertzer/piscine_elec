/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/19 10:38:42 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	timer1_init();
	uart_init();

	// set general interrupts
	sei();

	while (true)
	{
	}
	return 0;
}

void	timer1_init()
{
	/*timer 1 settings  mode 15*/
	TCCR1A =  1 << WGM11 | 1 << WGM10;
	// clock divided by 1024
	TCCR1B = 0b00011101;
	TIMSK1 |= (1 << TOIE1);
	/*frequency 0.5 Hz */
	OCR1A = F_CPU / 1024 * 2;
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

void	uart_printstr(char *str)
{
	while (*str != '\0')
	{
		uart_tx(*str);
		++str;
	}
}

// timer0 interrupt handling
ISR(TIMER1_OVF_vect)
{
	uart_printstr("Hello World!\r\n");
}
