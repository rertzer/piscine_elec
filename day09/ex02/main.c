/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/26 12:16:37 by rertzer          ###   ########.fr       */
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
	i2c_write(0b01111111);
	i2c_write(0b00000000);
	i2c_stop();
	
	
	while (1)
	{
	
		i2c_start();
		i2c_write(39 << 1);
		i2c_write(0x02);
		i2c_write(0b01111111);
		i2c_write(0b01011011);
		i2c_stop();

		_delay_ms(100);

	}
}
