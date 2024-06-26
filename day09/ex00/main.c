/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/26 15:26:52 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

int	main(void)
{
	i2c_init();

	bool	led9 = false;
	
	i2c_start();
	i2c_write(39 << 1);
	i2c_write(0x06);
	i2c_write(0b11110111);
	i2c_stop();
	
	while (1)
	{
		i2c_start();
		i2c_write(39 << 1);
		i2c_write(0x02);
		if (led9)
			i2c_write(0b11110111);
		else
			i2c_write(0b11111111);
		i2c_stop();

		led9 = ! led9;
		_delay_ms(500);
	}
}
