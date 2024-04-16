/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/16 17:24:06 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

int	main(void)
{
	/* set led as output */
	DDRB |= (1 << PB1);	

	/* TCCR: TIMER/COUNTER CONTROL REGISTER
	 * COMAx's defines OCx behaviour: OC1A switches on TOP
	 * WGMx defines which top value to use: 14
	 * CSx defines the clock prescaler  clkio/1024 */
	 
	/* COM1A1 COM1A0 . . . . WGM11 WGM10*/
	TCCR1A = 1 << COM1A1 | 1 << WGM11;
	/* . . . WGM13 WGM12 CS12 CS11 CS10*/
	TCCR1B = 0b00011101;

	/*TOP value: nb of cycle before OC1A increase*/
	///////////////////////////////////////////////////////////////////

	bool			button_1 = false;
	bool			button_2 = false;
	unsigned int	duty = 10;

	ICR1 = 15625;
	while (1)
	{
		/* PIND: read values on PORT D
		 * 0: pushed
		 * 1: not pushed
		 * PORTB: register for values on PORT B pins
		 * 0: low
		 * 1: high
		 */
		if (duty)
			OCR1A = 156 * duty;
		else
			OCR1A = 0;
		if ((PIND & (1 << PD2)))
		{
			button_1 = false;
		}
		else
		{
			if (button_1 == false)
			{
				if (duty < 100)
					duty += 10;
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
				if (duty != 0)
					duty -= 10;
				button_2 = true;
			}
		}

		_delay_ms(10);
	}
}
