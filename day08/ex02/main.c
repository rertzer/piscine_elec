/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/25 11:15:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"


void	led_color(uint8_t led, uint8_t r, uint8_t g, uint8_t b)
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
		_delay_ms(250);
}


int	main(void)
{

	spi_init();

	while (1)
	{
			led_color(0x01, 0x00, 0xFF, 0xFF);
			led_color(0x02, 0x00, 0xFF, 0xFF);
			led_color(0x03, 0x00, 0xFF, 0xFF);
			led_color(0x03, 0x00, 0x00, 0x00);
	}
}

