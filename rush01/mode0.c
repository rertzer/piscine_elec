/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 09:35:28 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/27 10:22:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	mode0()
{
	uint16_t	counter = 0;
	uint8_t		buffer[4];
	ADMUX = 0b01000000;
	ADCSRA = 0b10000111;
	while (1)
	{	
		counter = adc_read_channel(0x00);
		split_number(counter, buffer);
		for (int i = 0; i < 4; ++i)
			write_digit(buffer[i], i);
	}
}
