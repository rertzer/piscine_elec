/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/24 10:27:36 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	adc_read_channel(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC);
	//wait for read done
	while ( ADCSRA & (1<<ADSC));
	uart_print_hex(ADCH);

}

int	main(void)
{
	uart_init();
	sei();
	
	//AVcc, Left adjust, ,channel ADC0
	//..      .         -  ....  
	ADMUX = 0b01100000;
	//enable, ,prescaler 128
	//. ---- ...
	ADCSRA = 0b10000111;

	while (1)
	{
		//ADC0 potentiometer
		adc_read_channel(0x00);
		uart_printstr("\r\n");
		_delay_ms(20);
	}
}

