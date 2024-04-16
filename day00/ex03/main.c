/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/16 15:38:12 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

int	main(void)
{
	/*
	 * DDRB: Port B Data Direction Register
	 * to indicate whether port B pins are read or write
	 * 0: read
	 * 1: write
	 * PB0 a macro for PB0 offset in DDRB register (0)
	 */
	DDRB |= 1 << PB0;
	PORTB &= ~(1 << PB0);

	/* Switch 1 is on PORT D (PD2). DDRD is output by default
	 * setting port D to read;
	 * */
	//DDRD &= ~(1 << PD2);
	bool	button = false;
	while (1)
	{
		/* PIND: read values on PORT D
		 * 0: pushed
		 * 1: not pushed
		 * PORTB: register for values on PORT B pins
		 * 0: low
		 * 1: high
		 */
		if ((PIND & (1 << PD2)))
		{
			button = false;
		}
		else
		{
			if (button == false)
			{
				PORTB ^= (1 << PB0);
				button = true;
			}
		}
		_delay_ms(10);
	}
}
