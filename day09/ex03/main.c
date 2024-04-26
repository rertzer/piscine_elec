/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/26 13:08:17 by rertzer          ###   ########.fr       */
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

	bool	button = false;
	uint8_t	counter = 0;

	i2c_start();
	i2c_write(39 << 1);
	//command register 0
	i2c_write(0x06);
	i2c_write(0b01111111);
	i2c_write(0b00000000);
	i2c_stop();
	
	
		
	while (1)
	{	
		i2c_start();
		i2c_write(39 << 1);
		i2c_write(0x02);
		i2c_write(0b01111111);
		i2c_write(digits[counter]);
		i2c_stop();
		++counter;
		if (counter == 10)
			counter = 0;
		_delay_ms(1000);

	}
}
