/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/24 12:18:10 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

uint16_t	adc_read_channel(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC);
	//wait for read done
	while ( ADCSRA & (1<<ADSC));
	uint8_t	value = ADCH;
	wheel(value);
	if (value < 64)
		PORTB = (1<<PB0);
	else if (value < 128)
		PORTB = (1<<PB1);
	else if (value < 192)
		PORTB = (1<<PB2);
	else
		PORTB = (1<<PB4);
}

int	main(void)
{
	init_rgb();
	char	color[255]; 

	DDRB |= 1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4;
	PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);

	sei();
	
	//AVcc, left adjust, ,channel ADC0
	//..      .         -  ....  
	ADMUX = 0b01100000;
	//enable, ,prescaler 128
	//. ---- ...
	ADCSRA = 0b10000111;

	while (1)
	{
		//internal
		adc_read_channel(0x00);
		_delay_ms(20);
	}
}

