/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:15:20 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 09:50:10 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

// LDR
void	init_mode1()
{
	ADMUX = 0b01000000;
	ADCSRA = 0b10000111;
}

void	mode1()
{	
	adc_display_channel(0x01);
}