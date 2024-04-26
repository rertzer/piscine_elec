/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/26 15:50:16 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	init_7segments()
{
	i2c_start();
	i2c_write(39 << 1);
	i2c_write(0x06);
	i2c_write(0b00001111);
	i2c_write(0b00000000);
}

void	write_digit(uint8_t digit, uint8_t pos)
{
	pos = ~(1<<(7 - pos));

	uint8_t	digits[10];
	digits[0] = 0b00111111;
	digits[1] = 0b00000110;
	digits[2] = 0b01011011;
	digits[3] = 0b01001111;
	digits[4] = 0b01100110;
	digits[5] = 0b01101101;
	digits[6] = 0b01111101;
	digits[7] = 0b00000111;
	digits[8] = 0b01111111;
	digits[9] = 0b01101111;

	i2c_start();
	i2c_write(39 << 1);
	i2c_write(0x02);
	i2c_write(pos);
	i2c_write(digits[digit]);
	i2c_start();
	i2c_write(39 << 1);
	i2c_write(0x02);
	i2c_write(0b11111111);
	i2c_write(0);
	i2c_stop();
}

int	main(void)
{
	uint16_t	counter = 0;
	uint16_t	little_counter = 0;
	uint8_t		buffer[4];
	
	i2c_init();
	init_7segments();
	
	while (1)
	{	
		split_number(counter, buffer);
		for (int i = 0; i < 4; ++i)
			write_digit(buffer[i], i);
		++little_counter;
		if (little_counter == 250)
		{
			++counter;
			little_counter = 0;
		}
		if (counter == 10000)
			counter = 0;
		_delay_ms(1);
	}
}
