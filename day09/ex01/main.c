/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 18:17:30 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"


void	display_status(uint8_t status)
{
	uart_printstr("status is: ");
	uart_print_hex(status);
	uart_printstr("\r\n");
}

int	main(void)
{
	uart_init();
	i2c_init();
	//spi_init();

	bool	button = false;
	uint8_t	counter = 0;

	i2c_start();
	i2c_write(39 << 1);
	//command register 0
	i2c_write(0x06);
	i2c_write(0b11110001);
	i2c_stop();
	
	
	while (1)
	{
		//read button
		i2c_start();
		i2c_write(39 << 1);
		i2c_write(0x00);
		i2c_stop();
		i2c_start();
		i2c_write(39 << 1 | 1);
		i2c_last_read();
		i2c_stop();
		if ((TWDR & 0x01))
		{
			button = false;
		}
		else
		{
			if (button == false)
			{
				++counter;
				button = true;
			}
		}
		i2c_start();
		i2c_write(39 << 1);
		i2c_write(0x02);
		uint8_t	input = ~( ((counter & 0x07)<<1));
		i2c_write(input);
		i2c_stop();

		_delay_ms(100);

	}
}
