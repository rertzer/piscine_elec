/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/19 15:07:35 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

int	main(void)
{
	sei();
	uart_init();

	i2c_init();
	i2c_start();
	i2c_stop();

	while (true)
	{
	}
	return 0;
}

void	display_status(uint8_t status)
{
	uart_printstr("status is: ");
	uart_print_hex(status);
	uart_printstr("\r\n");
}
