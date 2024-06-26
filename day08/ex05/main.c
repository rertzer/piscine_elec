/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/26 09:16:38 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"


void	led_color(uint8_t *frame, uint8_t led, uint8_t color, uint8_t value)
{
	
		frame[5 + 4*led + color] = value;
		spi_transmit_buffer(frame, LED_FRAME_SIZE);
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
	
	uint8_t	frame[LED_FRAME_SIZE]= {
		0x00, 0x00, 0x00, 0x00,
		0xB1, 0x00, 0x00, 0x00,
		0xB1, 0x00, 0x00, 0x00,
		0xB1, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF,
	};
	uint8_t	led = 0;
	uint8_t	color = 0;
	bool	sw1 = false;
	bool	sw2 = false;

	while (1)
	{
		//sw2
		if ((PIND & (1 << PD2)))
		{
			sw1 = false;
		}
		else
		{
			if (sw1 == false)
			{
				uint8_t	value = adc_read_channel(0x00);
				led_color(frame, led, color, value);
				++color;
				if (color > 2)
					color = 0;
				sw1 = true;
			}
		}
		if ((PIND & (1<<PD4)))
		{
			sw2 = false;
		}
		else
		{
			if (sw2 == false)
			{
				++led;
				if (led > 2)
					led = 0;
				sw2 = true;
			}
		}
		_delay_ms(20);
	}
}
