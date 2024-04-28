/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 09:30:27 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 12:13:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	adc_display_channel(uint8_t channel)
{
	uint16_t	counter = 0;
	counter = adc_read_channel(channel);
	write_number(counter);
}

uint16_t	adc_read_channel(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC);
	while ( ADCSRA & (1<<ADSC));
	return ADC;
}
