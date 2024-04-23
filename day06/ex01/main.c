/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/23 13:27:42 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"
int		duty = 1;
bool	ascending = true;

void	init_rgb()
{
	/* set led as output */
	DDRD |= 1 << PD3 | 1 << PD5 | 1 << PD6;
	PORTD &= ~(1 << PD3 | 1 << PD5 | 1 << PD6);
}

int	main(void)
{
	init_rgb();

	uint8_t	rainbow[7];
	rainbow[0] = RED;
	rainbow[1] = GREEN;
	rainbow[2] = BLUE;
	rainbow[3] = RED | GREEN;
	rainbow[4] = GREEN | BLUE;
	rainbow[5] = RED | BLUE;
	rainbow[6] = RED | GREEN | BLUE;
	
	uint8_t	pos = 0;
	while (1)
	{
		PORTD = rainbow[pos];
		
		++pos;
		if (pos > 6)
			pos = 0;
		_delay_ms(1000);
	}
}
