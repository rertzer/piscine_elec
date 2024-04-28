/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:21:10 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 14:38:21 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ATmega.h"

void	init_mode6()
{
	// turn off mode 4
	if (SPCR & 1<<SPE)
		spi_led_tricolor(0, 0, 0);
	PORTD &= ~(1 << PD3 | 1 << PD5 | 1 << PD6);
	DDRD = 0;
	SPCR = 0;
	value = 0;
}

void	mode6()
{
	write_number(value);
}
