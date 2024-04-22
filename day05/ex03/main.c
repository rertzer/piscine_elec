/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/22 11:28:22 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

int	main(void)
{
	//led setting
	DDRB |= 1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4;
	PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);

	bool			led = false;
	bool			button_1 = false;
	bool			button_2 = false;
	uint8_t			counter;
	unsigned int	counter_address = 0;
	uint8_t			count;
	unsigned int	count_address = 1;

	counter = eeprom_read(counter_address);
	if (counter > 3)
	{
		zeros(counter_address, 5);
		counter = 0;
	}
	count = eeprom_read(count_address + counter);

	while (1)
	{
		if ((PIND & (1 << PD2)))
		{
			button_1 = false;
		}
		else
		{
			if (button_1 == false)
			{
				++count;
				eeprom_write(count_address + counter, count);
				button_1 = true;
			}
		}
		
		if ((PIND & (1 << PD4)))
		{
			button_2 = false;
		}
		else
		{
			if (button_2 == false)
			{
				++counter;
				if (counter == 4)
					counter = 0;
				eeprom_write(counter_address, counter);
				count	= eeprom_read(count_address + counter);
				button_2 = true;
			}
		}
		int	led_1 = (count & 0b00000001) ;
		int	led_2 = (count & 0b00000010) ;
		int led_3 = (count & 0b00000100) ;
		int	led_4 = (count & 0b00001000) << 1;

		PORTB = led_1 | led_2 | led_3 | led_4;

		_delay_ms(10);
	}
}

void	zeros(unsigned int address, unsigned int size)
{
	for (int i = 0; i < size; ++i)
	{
		eeprom_write(address + i, 0);
	}
}
