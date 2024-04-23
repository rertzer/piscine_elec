/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/23 14:24:42 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	init_rgb()
{
	/* set led as output */
	DDRD |= 1 << PD3 | 1 << PD5 | 1 << PD6;
	PORTD &= ~(1 << PD3 | 1 << PD5 | 1 << PD6);
	/* timer 0 settings A: green, B: red */
	TCCR0A = (1<<COM0A1) | (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);
	TCCR0B = (1<<CS02) | (1<<CS00);
	OCR0A = 0;
	OCR0B = 0;

	/*timer 2 B: blue */
	TCCR2A =  (1<<COM2B1) | (1<<WGM21) | (1<<WGM20);
	TCCR2B = (1<<CS22) | (1<<CS20);
	OCR2B = 0;

}

void	set_rgb(uint8_t *rgb)
{
	OCR0A = rgb[1];
	OCR0B = rgb[0];
	OCR2B = rgb[2];
}

int	main(void)
{
	init_rgb();
	uart_init();
	uint8_t	rgb[3] = {255, 255, 255};
	char	color[255];
	set_rgb(rgb);

	while (1)
	{
		uart_print("\r\nEnter a color: ");
		read_line(color);
		set_colors(color, rgb);
		set_rgb(rgb);
		_delay_ms(50);
	}
}

uint8_t	color_value(uint8_t x)
{
	if (x >= '0' && x <= '9')
		return x - '0';
	if (x >= 'A' && x <= 'F')
		return x - 'A' + 10;
	return 0;
}

uint8_t	read_color(uint8_t msb, uint8_t lsb)
{
	return color_value(msb) << 4 | color_value(lsb);
}

void	set_colors(char *color, uint8_t *rgb)
{
	if ((ft_strlen(color) != 7) || color[0] != '#')
		return;
	for (int i = 0; i < 3; ++i)
	{
		rgb[i] = read_color(color[1 + 2 * i], color[2 + 2 * i]);
	}
}
