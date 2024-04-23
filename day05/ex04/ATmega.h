/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATmega.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:17:42 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/23 10:33:36 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATMEGA_H
#define ATMEGA_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>


enum command	{INVALID, READ, WRITE, FORGET};


#define	START 1
#define	BAUDO 115200
#define	MAGIC_EEPROM 0x42
#define	KEY		0xA0
#define	VALUE	0xB0


//eeprom
unsigned char	eeprom_read(unsigned int address);
void			eeprom_write(unsigned int address, unsigned char data);
bool			eepromalloc_init(uint16_t length);
bool			eepromalloc_write(uint16_t id, void *buffer, uint16_t length);
bool			eepromalloc_newrite(uint16_t id, void *buffer, uint16_t length);
bool			eepromalloc_rewrite(uint16_t address, void *buffer, uint16_t length);
bool			eepromalloc_read(uint16_t id, void *buffer, uint16_t length);
bool			eepromalloc_free(uint16_t id);
uint16_t		eeprom_find_id(uint16_t id);
uint16_t		eeprom_find_empty(uint16_t length);
bool			eeprom_buffer_write(void *buffer, uint16_t offset, uint16_t length);
bool			safe_eeprom_write(void *buffer, uint16_t offset, uint16_t length);

// uart
void	uart_init();
char	uart_rx();
void	uart_tx(char c);
void	uart_printstr(char *str);
void	uart_print_hex(uint8_t value);
void	ft_itoa_hex(uint16_t nb, char *buffer);

// ft_strcmp
int	ft_strcmp(const char *s1, const char *s2);
#endif
