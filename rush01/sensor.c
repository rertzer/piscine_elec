/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sensor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:15:50 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 15:06:55 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	trigger_measure()
{
	sensor_start_write();
	i2c_write(0xAC);
	i2c_write(0x33);
	i2c_write(0x00);
	i2c_stop();
	delay_mode(80);
}

void	sensor_read()
{
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
	delay_mode(80);
	sensor_start_write();
	i2c_write(reg);
	i2c_write(0x00);
	i2c_stop();
}

void	sensor_status()
{
	sensor_read();
	if (TWDR == 0x18)
	{
		i2c_stop();
		sensor_register_init(0x1B);
		sensor_register_init(0x1C);
		sensor_register_init(0x1E);
		sensor_start_write();
		delay_mode(10);
		trigger_measure();
		sensor_read();
	}
}
