/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/19 09:45:20 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	char	username[255];
	char	password[255];

	uart_init();

	//setting LEDs
	DDRB |= 1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4;
	PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);

	while (true)
	{

		uart_print("Enter your login:\r\n");
		uart_print("\tusername: ");
		read_line(username, false);
		uart_print("\r\n\tpassword: ");
		read_line(password, true);
		if (granted(username, password))
		{
			greet(username);
			fireworks();
		}
		else
			boo(username);
		
	}
	return 0;
}

void	read_line(char* buffer, bool hidden)
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
			if (hidden)
				c = '*';
		}
		uart_tx(c);
	}
	buffer[i] = '\0';
}

bool	granted(char *username, char *password)
{
	if (! ft_strcmp(username, "rantanplan") && ! ft_strcmp(password, "pate"))
		return true;
	else
		return false;
}

void	greet(char* username)
{
	uart_print("\r\nOuaf Ouaf, ");
	uart_print(username);
	uart_print(" !!!\r\n");
}

void	boo(char *username)
{
	uart_print("How dare you, filthy ******* !!!!!\r\n");
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

void	fireworks()
{
	while(true)
	{
		PORTB = 0b00010001;
		_delay_ms(1000);
		PORTB = 0b00000110;
		_delay_ms(1000);
	}
}
