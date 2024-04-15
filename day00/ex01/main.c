/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:31:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/15 12:58:02 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

int	main()
{
	/*
	 * DDRB: Port B Data Direction Register
	 * to indicate whether port B pins are read or write
	 * 0: read
	 * 1: write
	 * PB0 a macro for PB0 offset in DDRB register (0)
	 */
	DDRB |= 1 << PB0;
	/* PORTB: register for values on PORT B pins
	 * 0: low
	 * 1: high
	 */
	PORTB |= 1 << PB0;
}
