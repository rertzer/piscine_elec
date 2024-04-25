/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATmega.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:17:42 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/25 15:31:28 by rertzer          ###   ########.fr       */
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
uint8_t	color_value(uint8_t x);
uint8_t	read_color(uint8_t msb, uint8_t lsb);
void	set_colors(char *color, uint8_t *rgb);


//I2C
void	i2c_init();
void	i2c_start();
void	i2c_stop();
void	i2c_write(unsigned int char);
void	i2c_read();

//SPI
void	spi_init();
void	spi_transmit(uint8_t data);
void	spi_transmit_buffer(uint8_t *buffer, uint16_t size);


//uart
void	uart_init();
char	uart_rx();
void	uart_tx(char c);
void	uart_printstr(char *str);
void	uart_print_hex(uint8_t value);
void	uart_print_dec(uint16_t value);

void	ft_itoa_hex(uint16_t nb, char *buffer);
void	ft_itoa_dec(uint16_t nb, char *buffer);
#endif

