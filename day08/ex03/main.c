/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/25 11:35:46 by rertzer          ###   ########.fr       */
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

		frame[5 + 4*led] = b;
		frame[6 + 4*led] = g;
		frame[7 + 4*led] = r;
		spi_transmit_buffer(frame, LED_FRAME_SIZE);
		_delay_ms(20);
}

uint8_t	adc_read_channel(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC);
	//wait for read done
	while ( ADCSRA & (1<<ADSC));
	return ADCH;
}

int	main(void)
{
	ADMUX = 0b01100000;
	ADCSRA = 0b10000111;
	spi_init();

	while (1)
	{
			uint8_t	value = adc_read_channel(0x00);
			value /= 86;
			led_color(value, 0xFF, 0x7F, 0x00);
	}
}

