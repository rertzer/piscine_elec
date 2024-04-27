/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATmega.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:17:42 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/27 11:29:26 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATMEGA_H
#define ATMEGA_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define	BAUDO	115200
#define	TIMER1_TOP 312

#define	RED		(1<<PD3)
#define	GREEN	(1<<PD5)
#define	BLUE	(1<<PD6)

#define	LED_FRAME_SIZE	20

volatile uint8_t	mode;
volatile bool	top;


void	display_status(uint8_t status);


//timer 1
void	set_timer1();

//switches
void	init_switches();
void	led_switches();
void	expander_led(uint8_t led);
bool	read_button_sw3();

// 7 segments
void	init_7segments();
void	write_digit(uint8_t digit, uint8_t pos);

// mode 0
void	mode0();

//I2C
void	i2c_init();
void	i2c_start();
void	i2c_stop();
void	i2c_write(unsigned char value);
void	i2c_read();
void	i2c_last_read();

//SPI
void	spi_init();
void	spi_transmit(uint8_t data);
void	spi_transmit_buffer(uint8_t *buffer, uint16_t size);

//adc
uint16_t	adc_read_channel(uint8_t channel);

//uart
void	uart_init();
char	uart_rx();
void	uart_tx(char c);
void	uart_printstr(char *str);
void	uart_print_hex(uint8_t value);
void	uart_print_dec(uint16_t value);

//sensor
void	trigger_measure();
void	sensor_read();
void	sensor_start_write();
void	sensor_register_init(uint8_t reg);
void	sensor_status();

//
void	ft_itoa_hex(uint16_t nb, char *buffer);
void	ft_itoa_dec(uint16_t nb, char *buffer);
void	split_number(uint16_t nb, uint8_t *buffer);
#endif

