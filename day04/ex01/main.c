/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/20 11:33:17 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

int	main(void)
{
	sei();
	uart_init();

	i2c_init();
	
	while (true)
	{
		trigger_measure();
		sensor_status();
		for (int i = 0; i < 6; ++i)
		{
			i2c_read();
			uart_printstr("data received is: ");
			uart_print_hex(TWDR);
			uart_printstr("\r\n");
		}
		_delay_ms(1000);
	}
	i2c_stop();
	return 0;
}

void	display_status(uint8_t status)
{
	uart_printstr("status is: ");
	uart_print_hex(status);
	uart_printstr("\r\n");
}

void	print_hex_value(char c)
{
	uart_print_hex(c);
}
