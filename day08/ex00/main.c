/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/25 10:46:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"




int	main(void)
{
	//start B G R stop
	uint8_t	frame[LED_FRAME_SIZE]= {
		0x00, 0x00, 0x00, 0x00,
		0xEF, 0x00, 0x00, 0xFF,
		0xE0, 0x00, 0x00, 0x00,
		0xE0, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF,
	};

	spi_init();
	spi_transmit_buffer(frame, LED_FRAME_SIZE);

	while (1)
	{
		_delay_ms(1000);
	}
}

