/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sensor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:15:50 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/20 16:12:35 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	trigger_measure()
{
	sensor_start_write();
	//uart_printstr("trigger measure\r\n");
	_delay_ms(10);
	i2c_write(0xAC);
	i2c_write(0x33);
	i2c_write(0x00);
	_delay_ms(80);
}

void	sensor_read()
{
	//uart_printstr("sensor read\r\n");
	i2c_start();
	i2c_write((0x38 << 1) | 1);
	i2c_read();
}

void	sensor_start_write()
{
	i2c_start();
	i2c_write(0x38 << 1);

}

void	sensor_register_init(uint8_t reg)
{
	_delay_ms(80);
	uart_printstr("init register\r\n");
	sensor_start_write();
	i2c_write(reg);
	i2c_write(0x00);
	i2c_stop();
}

void	sensor_status()
{
	//uart_printstr("sensor status\r\n");
	sensor_read();
	//uart_printstr("sensor ");
	if (TWDR == 0x18)
	{
		uart_printstr("received status 0x18... initializing...\r\n");
		i2c_stop();
		sensor_register_init(0x1B);
		sensor_register_init(0x1C);
		sensor_register_init(0x1E);
		sensor_start_write();
		_delay_ms(10);	
		trigger_measure();
		sensor_read();
	}
//	while ((TWDR & 0x80) == 0x80)
//	{
//		uart_printstr("busy...\r\n");
//		i2c_stop();
//		_delay_ms(80);
//		trigger_measure();
//		sensor_read();
//	}
//	display_status(TWDR);
}
