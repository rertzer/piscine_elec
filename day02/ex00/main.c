/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/17 14:38:34 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
 * INT0 falling edge trigger ISC01=1 | ISC00=0 
*/



ISR(INT0_vect)
{
	PORTB ^= (1 << PB0);
}


int	main(void)
{
	/* set led as output */
	DDRB |= (1 << PB0);	

	/* switch 1 interrupt */
	sei();
	EICRA |= 1 << ISC01;
	EIMSK |= 1 << INT0;

	while (1)
	{
		_delay_ms(10);
	}
}
