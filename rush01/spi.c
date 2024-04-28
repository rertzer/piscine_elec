/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:03:28 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 11:24:51 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"
void	spi_init()
{
	DDRB |= (1<<PB2) | (1<<PB3) | (1<<PB5);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}

void	spi_transmit(uint8_t data)
{
	SPDR = data;
	while (! (SPSR & (1<<SPIF)));
}

void	spi_transmit_buffer(uint8_t	*buffer, uint16_t size)
{
	for (uint16_t i = 0; i < size; ++i)
	{
		spi_transmit(buffer[i]);
	}
}

void	spi_led_color(uint8_t led, uint8_t r, uint8_t g, uint8_t b)
{	//start B G R stop
	uint8_t	frame[LED_FRAME_SIZE]= {
		0x00, 0x00, 0x00, 0x00,
		0xEF, 0x00, 0x00, 0x00,
		0xEF, 0x00, 0x00, 0x00,
		0xEF, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF,
	};

		frame[1 + 4*led] = b;
		frame[2 + 4*led] = g;
		frame[3 + 4*led] = r;
		spi_transmit_buffer(frame, LED_FRAME_SIZE);
}

void	spi_led_tricolor(uint8_t r, uint8_t g, uint8_t b)
{	//start B G R stop
	uint8_t	frame[LED_FRAME_SIZE]= {
		0x00, 0x00, 0x00, 0x00,
		0xEF, 0x00, 0x00, 0x00,
		0xEF, 0x00, 0x00, 0x00,
		0xEF, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF,
	};

		for (int led = 1; led < 4; ++led)
		{
			frame[1 + 4*led] = b;
			frame[2 + 4*led] = g;
			frame[3 + 4*led] = r;
		}
		spi_transmit_buffer(frame, LED_FRAME_SIZE);
}
