/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/17 15:27:16 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* DAY02 EX01 */

/*
 * INT0 falling edge trigger ISC01=1 | ISC00=0 
*/

#define	TIMER1_TOP 100

int		duty = 1;
bool	ascending = true;

ISR(TIMER0_OVF_vect)
{
	if (ascending)
	{
		if (duty >= 100)
		{
			duty = 99;
			ascending = false;
		}
		else
			++duty;
	}
	else
	{
		if (duty <= 0)
		{
			duty = 1;
			ascending = true;
		}
		else
			--duty;
	}
		OCR1A = duty;
}


int	main(void)
{
	/* set led as output */
	DDRB |= (1 << PB1);	

	/*timer 0 settings mode 15*/
	TCCR0A = 0b11000011;
	TCCR0B = 0b00001101;
	OCR0A = 78;
	TIMSK0 = (1 << TOIE0);

	/* timer 1 settings mode 14*/
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = 0b00011101;
	OCR1A =  duty;
	ICR1 = TIMER1_TOP;

	sei();


	while (1)
	{
		_delay_ms(10);
	}
}
