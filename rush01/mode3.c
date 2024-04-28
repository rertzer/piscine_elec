/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:16:28 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 11:41:05 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ATmega.h"

void	init_mode3()
{
	// turn off mode 4
	if (SPCR & 1<<SPE)
		spi_led_tricolor(0, 0, 0);
	PORTD &= ~(1 << PD3 | 1 << PD5 | 1 << PD6);
	DDRD = 0;
	SPCR = 0;
	//
	ADMUX = 0b11000000;
	ADCSRA = 0b10000111;
}

void	mode3()
{	
	adc_display_channel(0x08);
}
