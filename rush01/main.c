/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/27 11:55:45 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

// 11 = init
extern volatile uint8_t	mode;
extern volatile bool	top;

void	init_sequence()
{
	top = false;
	mode = 11;
	while(! top)
	{
		_delay_ms(10);
	}
	//turn on all 7 segments and D1 D2 D3 during 3 seconds
	while (top)
	{
		for (int i = 0; i < 4; ++i)
			write_digit(10, i);
	}
	//turn off during 1 second
	_delay_ms(1000);
}


int	main(void)
{
	uint16_t	counter = 0;
	uint8_t		buffer[4];
	
	sei();
	set_timer1();
	i2c_init();
	uart_init();
	init_7segments();

	init_sequence();
	init_switches();
	mode = 0;
	while (1)
	{
		led_switches();
		_delay_ms(10);
	}

}
