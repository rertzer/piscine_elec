/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/25 14:37:15 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"


uint8_t	pos;
bool	rainbow;
uint8_t	frame[LED_FRAME_SIZE]= {
		0x00, 0x00, 0x00, 0x00,
		0xB1, 0x00, 0x00, 0x00,
		0xB1, 0x00, 0x00, 0x00,
		0xB1, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF,
	};


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

void	set_rgb(uint8_t *frame, uint8_t r, uint8_t g, uint8_t b)
{
	/*for (int i = 0; i < 3; ++i)
	{
		frame[5 + 4 * i] = b;
		frame[6 + 4 * i] = g;
		frame[7 + 4 * i] = r;
	}*/
	frame[5] = b;
	frame[6] = g;
	frame[7] = r;

	frame[9] = g;
	frame[10] = r;
	frame[11] = b;

	frame[13] = r;
	frame[14] = b;
	frame[15] = g;
}

void wheel(uint8_t pos, uint8_t *frame)
{
	pos = 255 - pos;
	if (pos < 85)
	{
		set_rgb(frame, 255 - pos * 3, 0, pos * 3);
	}
	else if (pos < 170)
	{
		pos = pos - 85;
		set_rgb(frame, 0, pos * 3, 255 - pos * 3);
	}
	else
	{
		pos = pos - 170;
		set_rgb(frame, pos * 3, 255 - pos * 3, 0);
	}
}

ISR(TIMER0_OVF_vect)
{
	if (rainbow)
	{
		++pos;
		wheel(pos, frame);
		spi_transmit_buffer(frame, LED_FRAME_SIZE);
	}
}


int	main(void)
{
	uart_init();
	spi_init();
	sei();
	//mode 7
	TCCR0A =  1 << WGM01 | 1 << WGM00;
	TCCR0B = 0b00001101;


	OCR0A = 240;
	TIMSK0 |=  (1<<TOIE0);
	uint8_t	buffer[255];
	pos = 0;
	rainbow = false;
	spi_transmit_buffer(frame, LED_FRAME_SIZE);

	while (1)
	{
		read_line(buffer);
		uart_print("\r\n");

		if (! ft_strcmp(buffer, "#FULLRAINBOW"))
		{
			rainbow = true;
			pos = 0;
			uart_print("rainbow mode\r\n");
		}
		else
			rainbow = false;

		if (!rainbow)
		{
			set_ledcolors(buffer, frame);
			spi_transmit_buffer(frame, LED_FRAME_SIZE);
		}
		_delay_ms(20);
	}
}

