/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/24 11:33:54 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

uint16_t	adc_read_channel(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC);
	//wait for read done
	while ( ADCSRA & (1<<ADSC));
	uint16_t	value = 0;
	value = ADCL & 0x00FF;
	value |= ((ADCH & 0x03) << 8) & 0xFF00;
	if (channel == 0x08)
	{
		value -= 342;
		value /= 1;
	}
	uart_print_dec(value);
}

int	main(void)
{
	uart_init();
	sei();
	
	//AVcc, right adjust, ,channel ADC0
	//..      .         -  ....  
	ADMUX = 0b11000000;
	//enable, ,prescaler 128
	//. ---- ...
	ADCSRA = 0b10000111;

	while (1)
	{
		//internal
		adc_read_channel(0x08);
		uart_printstr("\r\n");
		_delay_ms(1000);
	}
}

