/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:46:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/26 11:06:40 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"



void	led_color(uint8_t *frame, uint8_t led, uint8_t color, uint8_t value)
{	//start B G R stop
	
		frame[5 + 4*led + color] = value;
		spi_transmit_buffer(frame, LED_FRAME_SIZE);
}

uint8_t	adc_read_channel(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC);
	//wait for read done
	while ( ADCSRA & (1<<ADSC));
	return ADCH;
}

/*ISR(TIMER1_OVF_vect)
{	
	i2c_start();
	i2c_write(39 << 1);
	if (led9)
		i2c_write(0b11110111);
	else
		i2c_write(0b11111111);
	i2c_write(0);
	i2c_stop();
	//uart_printstr("top...");
	led9 = ! led9;
}
*/
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

	bool	led9 = false;
	//clock 1 setting mode 14
	TCCR1A =  1 << WGM11 ;
	TCCR1B = 0b00011101;

	ICR1 = F_CPU / 1024;
	TIMSK1 |=  (1<<TOIE1);

	i2c_start();
	i2c_write(39 << 1);
	//command register 0
	i2c_write(0x06);
	i2c_write(0b11110111);
	i2c_stop();
	
	//i2c_write(0);
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
