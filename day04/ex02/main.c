/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/20 15:55:38 by rertzer          ###   ########.fr       */
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
		double	temperature = 0.0;
		double	humidity = 0.0;
		for (int j = 0; j < 3; ++j)
		{
			trigger_measure();
			sensor_status();
			uint32_t	buffer[6];
			for (int i = 0; i < 6; ++i)
			{
				i2c_read();
				//uart_printstr("data received is: ");
				//uart_print_hex(TWDR);
				//uart_printstr("\r\n");
				buffer[i] = 0;
				buffer[i] = TWDR;
			}
			//temperature
			uint32_t uint_value = ((buffer[2] & 0x0F) << 16) | (buffer[3] << 8) | buffer[4];
			temperature += (double)uint_value / 1048576.0 * 200 - 50;

			//humidity
			uint_value = (buffer[0] << 12) | (buffer[1] << 4) | (((buffer[2] & 0xF0) >> 4));
			humidity += (((double)uint_value / 1048576.0) * 100.0);
			_delay_ms(1200);
		}
			temperature /= 3;
			humidity /= 3;
			//print temperature
			char	str_value[5];
			str_value[4] = '\0';
			char	*str_ref = dtostrf(temperature, 4, 1, str_value);
			uart_printstr("Temperature: ");
			uart_printstr(str_ref);

			//print humidity
			str_ref = dtostrf(humidity, 4, 1, str_value);
			uart_printstr("°C, Humidity: ");
			uart_printstr(str_ref);
			uart_printstr("%\r\n");
	}
	i2c_stop();
	while(true);
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
