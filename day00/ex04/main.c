/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/16 15:43:58 by rertzer          ###   ########.fr       */
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
	 * PBx a macro for PBx offset in DDRB register
	 */
	DDRB |= 1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4;
	PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);

	/* Switch 1 is on PORT D (PD2). DDRD is output by default
	 * setting port D to read;
	 * */
	//DDRD &= ~(1 << PD2);
	bool	led = false;
	bool	button_1 = false;
	bool	button_2 = false;
	int		count = 0;
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
			button_1 = false;
		}
		else
		{
			if (button_1 == false)
			{
				++count;
				button_1 = true;
			}
		}

		if ((PIND & (1 << PD4)))
		{
			button_2 = false;
		}
		else
		{
			if (button_2 == false)
			{
				--count;
				button_2 = true;
			}
		}

		int	led_1 = (count & 0b00000001) ;
		int	led_2 = (count & 0b00000010) ;
		int led_3 = (count & 0b00000100) ;
		int	led_4 = (count & 0b00001000) << 1;

		PORTB = led_1 | led_2 | led_3 | led_4;

		_delay_ms(10);
	}
}
