/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 15:07:47 by rertzer          ###   ########.fr       */
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

void	init_mode()
{
	void(*func[12])(void) = 
	{
		init_mode0,
		init_mode1,
		init_mode2,
		init_mode3,
		init_mode4,
		init_mode5,
		init_mode6,
		init_mode7,
		init_mode8,
		init_mode9,
		init_mode10,
		init_mode11,
	};
	(*func[mode])();

}


void	exec_mode()
{
	void(*func[12])(void) = 
	{
		mode0,
		mode1,
		mode2,
		mode3,
		mode4,
		mode5,
		mode6,
		mode7,
		mode8,
		mode9,
		mode10,
		mode11,
	};
	(*func[mode])();
}


void	delay_mode(int max)
{
	for (int i = 0; i < max; ++i)
	{
		exec_mode();
		_delay_ms(1);
	}
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
	init_mode();
	while (1)
	{
		cli();
		led_switches();
		exec_mode();
		sei();
	}

}
