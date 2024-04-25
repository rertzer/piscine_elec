/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/25 12:10:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"


uint8_t	color_value(uint8_t x)
{
	if (x >= '0' && x <= '9')
		return x - '0';
	if (x >= 'A' && x <= 'F')
		return x - 'A' + 10;
	return 0;
}

uint8_t	read_led(uint8_t led)
{
	return led - '6';
}

uint8_t	read_color(uint8_t msb, uint8_t lsb)
{
	return color_value(msb) << 4 | color_value(lsb);
}

void	set_ledcolors(char *ledcolor, uint8_t *frame)
{
	if ((ft_strlen(ledcolor) != 9) || ledcolor[0] != '#' || ledcolor[7] != 'D' )
	{
		uart_print("bad format\r\n");
		return;
	}
	for (int i = 0; i < 3; ++i)
	{
		uint8_t	led = read_led(ledcolor[8]);
		if (led > 2)
		{
			uart_print("bad formatr\n");
			return;
		}
		frame[5 + 4 * led + i] = read_color(ledcolor[1 + 2 * i], ledcolor[2 + 2 * i]);
	}
}

int	main(void)
{
	uart_init();
	spi_init();
	uint8_t	frame[LED_FRAME_SIZE]= {
		0x00, 0x00, 0x00, 0x00,
		0xEF, 0x00, 0x00, 0x00,
		0xEF, 0x00, 0x00, 0x00,
		0xEF, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF,
	};
	uint8_t	buffer[255];
	spi_transmit_buffer(frame, LED_FRAME_SIZE);

	while (1)
	{
		read_line(buffer);
		uart_print("\r\n");
		set_ledcolors(buffer, frame);
		spi_transmit_buffer(frame, LED_FRAME_SIZE);
		_delay_ms(20);
	}
}

