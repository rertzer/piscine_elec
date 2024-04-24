/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   led.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:54:24 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/24 12:06:13 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	init_rgb()
{
	/* set led as output */
	DDRD |= 1 << PD3 | 1 << PD5 | 1 << PD6;
	PORTD &= ~(1 << PD3 | 1 << PD5 | 1 << PD6);
	/* timer 0 settings A: green, B: red */
	TCCR0A = (1<<COM0A1) | (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);
	TCCR0B = (1<<CS02) | (1<<CS00);
	OCR0A = 0;
	OCR0B = 0;

	/*timer 2 B: blue */
	TCCR2A =  (1<<COM2B1) | (1<<WGM21) | (1<<WGM20);
	TCCR2B = (1<<CS22) | (1<<CS20);
	OCR2B = 0;

}

void	set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	OCR0A = r;
	OCR0B = g;
	OCR2B = b;
}

void wheel(uint8_t pos)
{
	pos = 255 - pos;
	if (pos < 85)
	{
		set_rgb(255 - pos * 3, 0, pos * 3);
	}
	else if (pos < 170)
	{
		pos = pos - 85;
		set_rgb(0, pos * 3, 255 - pos * 3);
	}
	else
	{
		pos = pos - 170;
		set_rgb(pos * 3, 255 - pos * 3, 0);
	}
}
