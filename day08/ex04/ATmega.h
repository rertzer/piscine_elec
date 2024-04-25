/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATmega.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:17:42 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/25 13:27:37 by rertzer          ###   ########.fr       */
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

//SPI
void	spi_init();
void	spi_transmit(uint8_t data);
void	spi_transmit_buffer(uint8_t *buffer, uint16_t size);


//uart prompt
void	read_line(char *buffer);
void	uart_init();
char	uart_rx();
void	uart_tx(char c);
void	uart_print(char *str);

uint8_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_itoa_hex(uint16_t nb, char *buffer);
void	ft_itoa_dec(uint16_t nb, char *buffer);
#endif

