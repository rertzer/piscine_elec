/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:03:28 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/25 10:52:07 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"
void	spi_init()
{
	DDRB |= (1<<PB2) | (1<<PB3) | (1<<PB5);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}

void	spi_transmit(uint8_t data)
{
	SPDR = data;
	while (! (SPSR & (1<<SPIF)));
}

void	spi_transmit_buffer(uint8_t	*buffer, uint16_t size)
{
	for (uint16_t i = 0; i < size; ++i)
	{
		spi_transmit(buffer[i]);
	}
}
