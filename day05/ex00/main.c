/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/22 10:50:28 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

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
	bool			led = false;
	bool			button_1 = false;
	uint8_t			count = 0;
	unsigned int	count_address = 0;
	count = eeprom_read(count_address);

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
				eeprom_write(count_address, count);
				button_1 = true;
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


