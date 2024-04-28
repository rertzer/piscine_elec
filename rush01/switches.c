/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switches.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:03:48 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 13:17:38 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

void	init_switches()
{	
	i2c_start();
	i2c_write(39 << 1);
	i2c_write(0x06);
	i2c_write(0b00000001);
	i2c_write(0b00000000);
	i2c_stop();
}

void	led_switches()
{
	static	bool	sw1_pushed = false;
	static	bool	sw2_pushed = false;
	uint8_t	led = 0;


	//SW1 pushed => LED9 on
	if ((PIND & (1<<PD2)))
	{
		sw1_pushed = false;
	}
	else
	{
		led |= 8;
		if (sw1_pushed == false)
		{
			if (mode == 4)
				mode = 6;
			else if (mode < 11)
				++mode;
			sw1_pushed = true;
			init_mode();
		}
	}
				
	//SW2 pushed => LED10 on
	if ((PIND & (1<<PD4)))
	{
		sw2_pushed = false;
	}
	else
	{
		led |= 4;
		if (sw2_pushed == false)
		{
			if (mode == 6)
				mode = 4;
			else if (mode > 0)
				--mode;
			sw2_pushed = true;
			init_mode();
		}
	}

	//SW3 pushed => LED11 on
	if (read_button_sw3())
		led |= 2;
	expander_led(led);
}

void	expander_led(uint8_t led)
{
	i2c_start();
	i2c_write(39 << 1);
	i2c_write(0x02);
	i2c_write(~led);
	i2c_stop();
}

bool	read_button_sw3()
{
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
			return false;
		}
		return true;
}
