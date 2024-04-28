/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:56:17 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/28 17:27:20 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"


void	set_time()
{
	uint8_t	buffer[255];
	while (1)
	{
		uart_printstr("Enter current time and date (format dd/mm/yyyy hh:mm:ss):\r\n");
		readline(buffer);
		if (ft_strlen(buffer) != 19 ||
				buffer[2] != '/' ||
				buffer[5] != '/' ||
				buffer[10] != ' ' ||
				buffer[13] != ':' ||
				buffer[16] != ':')
		{
			uart_printstr("\r\nBad format\r\n");
			continue;
		}
		break ;
	}

}
