/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATmega.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:17:42 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/19 17:30:39 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATMEGA_H
#define ATMEGA_H

#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



#define	START 1
#define	BAUDO 115200

void	display_status(uint8_t status);

//I2C
void	i2c_init();
void	i2c_start();
void	i2c_stop();
void	i2c_write(unsigned char data);
char	i2c_read();

// uart
void	uart_init();
char	uart_rx();
void	uart_tx(char c);
void	uart_printstr(char *str);
void	uart_print_hex(uint8_t value);

//miscellanous
void	ft_itoa_hex(uint16_t nb, char *buffer);
void	print_hex_value(char c);
#endif
