/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/25 11:05:10 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"


void	led_color(uint8_t r, uint8_t g, uint8_t b)
{	//start B G R stop
	uint8_t	frame[LED_FRAME_SIZE]= {
		0x00, 0x00, 0x00, 0x00,
		0xEF, 0x00, 0x00, 0x00,
		0xE0, 0x00, 0x00, 0x00,
		0xE0, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF,
	};

		frame[5] = b;
		frame[6] = g;
		frame[7] = r;
		spi_transmit_buffer(frame, LED_FRAME_SIZE);
		_delay_ms(1000);
}


int	main(void)
{

	spi_init();

	while (1)
	{
		led_color(0xFF, 0x00, 0x00);
		led_color(0x00, 0xFF, 0x00);
		led_color(0x00, 0x00, 0xFF);
		led_color(0xFF, 0xFF, 0x00);
		led_color(0x00, 0xFF, 0xFF);
		led_color(0xFF, 0x00, 0xFF);
		led_color(0xFF, 0xFF, 0xFF);
	}
}

