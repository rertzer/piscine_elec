/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:17:42 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/19 09:44:06 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define	BAUDO 115200

void	uart_init();
void	uart_tx(char c);
char	uart_rx();
void	uart_print(char *str);
void	read_line(char *bufferi, bool hidden);
bool	granted(char *username, char *password);
void	greet(char *username);
void	boo(char *username);
void	fireworks();
int		ft_strcmp(const char *s1, const char *s2);
