/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/16 14:35:45 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

int	main(void)
{
	/* set led as output */
	DDRB |= (1 << PB1);	

	/* TCCR: TIMER/COUNTER CONTROL REGISTER
	 * COMAx's defines OCx behaviour: OC1A switches on TOP
	 * WGMx defines which top value to use: 15
	 * CSx defines the clock prescaler  clkio/1024 */
	 
	/* COM1A1 COM1A0 . . . . WGM11 WGM10*/
	TCCR1A = 1 << COM1A0;
	/* . . . WGM13 WGM12 CS12 CS11 CS10*/
	TCCR1B = 0b00001101;

	/*TOP value: nb of cycle before OC1A increase*/
	OCR1A = F_CPU / 1024 -1;

	while (1)
	{
		/*
		 * Śūnyatā (/ʃuːnjəˈtɑː/ shoon-yə-TAH; Sanskrit: शून्यता; Pali: suññatā),
		 * translated most often as "emptiness",[1] "vacuity", and sometimes
		 * "voidness",[2] or "nothingness"[3] is an Indian philosophical concept.
		 * Within Hinduism, Jainism, Buddhism, and other philosophical strands,
		 * the concept has multiple meanings depending on its doctrinal context.
		 * It is either an ontological feature of reality, a meditative state, or
		 * a phenomenological analysis of experience. */
	}
}
