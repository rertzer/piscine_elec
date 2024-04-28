/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:56:44 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 15:57:14 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

extern volatile uint8_t		mode;
extern volatile bool		top;
extern volatile uint16_t	value;

void	set_timer1()
{
	TCCR1A = 0b00000010;
	TCCR1B = 0b00011101;
	TIMSK1 = 0b00000001;
	ICR1 = F_CPU / 2048;
}

ISR(TIMER1_OVF_vect)
{
	if (mode == 4)
	{
		flash_tricolor();
	}
	else if (mode == 6)
	{
		take_celsius();
	}
	else if (mode == 7)
	{
		take_farenheit();
	}
	else if (mode == 8)
	{
		take_humidity();
	}
	else if (mode >= 11 && mode <= 16)
	{
		top = true;
		++mode;
	}
	else if (mode >= 17 && mode <= 18)
	{
		top = false;
		++mode;
	}
	else
		top = true;
}

void	flash_tricolor()
{
	static uint8_t	pos = 0;
	uint8_t	rainbow[3] = {RED, GREEN, BLUE};
	uint8_t rgb[3][3] = {{0xFF, 0x00, 0x00}, {0x00, 0xFF, 0x00}, {0x00, 0x00, 0xFF}};
		
	PORTD = rainbow[pos/2];
	spi_led_tricolor(rgb[pos/2][0], rgb[pos/2][1], rgb[pos/2][2]);
		++pos;
		if (pos > 5)
			pos = 0;
}

float	read_temperature()
{
		uint32_t	buffer[6];
	read_sensor(buffer);
	uint32_t temp = ((buffer[2] & 0x0F) << 16) | (buffer[3] << 8) | buffer[4];
	float ftemp = (float)temp / 1048576.0 * 200.0 - 50.0;
	return ftemp;
}

void	take_celsius()
{
	static bool	odd = true;

	odd = ! odd;
	if (odd)
		return;

	float ftemp = read_temperature();
	value = (uint16_t)ftemp;
}

void	take_farenheit()
{
	static bool	odd = true;

	odd = ! odd;
	if (odd)
		return;

	float ftemp = read_temperature();
	ftemp = ftemp * 9.0 / 5.0  + 32;
	value = (uint16_t)ftemp;
}

void	take_humidity()
{
	static bool	odd = true;

	odd = ! odd;
	if (odd)
		return;

	uint32_t	buffer[6];
	read_sensor(buffer);
	uint32_t hum = (buffer[0] << 12) | (buffer[1] << 4) | (((buffer[2] & 0xF0) >> 4));
	float fhum = ((float)hum / 1048576.0) * 100.0;
	value = (uint16_t)fhum;
}

void	read_sensor(uint32_t *buffer)
{
	trigger_measure();
	sensor_status();
	for (int i = 0; i < 6; ++i)
	{
		if (i != 5)
			i2c_read();
		else
			i2c_last_read();
		buffer[i] = 0;
		buffer[i] = TWDR;
	}
	i2c_stop();
}
