/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATmega.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:17:42 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 17:23:36 by rertzer          ###   ########.fr       */
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

#define	RED		(1<<PD5)
#define	GREEN	(1<<PD6)
#define	BLUE	(1<<PD3)

#define	LED_FRAME_SIZE	20

volatile uint8_t	mode;
volatile bool		top;
volatile uint16_t	value;

void	init_sequence();
void	init_mode();
void	exec_mode();
void	display_status(uint8_t status);
void	delay_mode(int max);

//timer 1
void	set_timer1();
void	flash_tricolor();
void	read_sensor(uint32_t *buffer);
float	read_temperature();
void	take_celsius();
void	take_farenheit();
void	take_humidity();

//rtc
void	set_time();

//switches
void	init_switches();
void	led_switches();
void	expander_led(uint8_t led);
bool	read_button_sw3();

// 7 segments
void	init_7segments();
void	write_number(uint16_t nb);
void	write_digit(uint8_t digit, uint8_t pos);
void	write_ft();

// modes
void	init_mode0();
void	init_mode1();
void	init_mode2();
void	init_mode3();
void	init_mode4();
void	init_mode5();
void	init_mode6();
void	init_mode7();
void	init_mode8();
void	init_mode9();
void	init_mode10();
void	init_mode11();

void	mode0();
void	mode1();
void	mode2();
void	mode3();
void	mode4();
void	mode5();
void	mode6();
void	mode7();
void	mode8();
void	mode9();
void	mode10();
void	mode11();

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
void	spi_led_color(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
void	spi_led_tricolor(uint8_t r, uint8_t g, uint8_t b);

//adc
void		adc_display_channel(uint8_t channel);
uint16_t	adc_read_channel(uint8_t channel);

//uart
void	uart_init();
char	uart_rx();
void	uart_tx(char c);
void	uart_printstr(char *str);
void	uart_print_hex(uint8_t value);
void	uart_print_dec(uint16_t value);

//uart prompt
void	readline(uint8_t *buffer);

//sensor
void	trigger_measure();
void	sensor_read();
void	sensor_start_write();
void	sensor_register_init(uint8_t reg);
void	sensor_status();

//
void	ft_itoa_hex(uint16_t nb, char *buffer);
void	ft_itoa_dec(uint16_t nb, char *buffer);
uint8_t	ft_strlen(const char *s);
void	split_number(uint16_t nb, uint8_t *buffer);
#endif

