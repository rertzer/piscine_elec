/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:56:44 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/27 11:28:25 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

extern volatile uint8_t	mode;
extern volatile bool	top;

void	set_timer1()
{
	TCCR1A = 0b00000010;
	TCCR1B = 0b00011101;
	TIMSK1 = 0b00000001;
	ICR1 = F_CPU / 2048;
}

ISR(TIMER1_OVF_vect)
{
	if (mode >= 11 && mode <= 16)
	{
		top = true;
		++mode;
	}
	else if (mode >= 17 && mode <= 18)
	{
		top = false;
		++mode;
	}
	else
		top = true;
}
