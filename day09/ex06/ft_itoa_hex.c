/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:44:16 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/19 15:36:58 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

static char	*chop_nbr_hex(char *buffer, uint16_t nb, uint16_t len)
{
	char	base[17] = "0123456789ABCDEF";
	while (nb / 16)
	{
		--len;
		buffer[len] = base[nb % 16];
		nb = nb / 16;
	}
	buffer[len - 1] = base[nb % 16];
	return (buffer);
}

static uint16_t	ft_getlen_hex(uint16_t nb)
{
	uint16_t	len;

	len = 1;
	while (nb / 16)
	{
		nb = nb / 16;
		++len;
	}
	return (len);
}

void	ft_itoa_hex(uint16_t nb, char *buffer)
{
	uint16_t	len;
	char		*str;

	len = ft_getlen_hex(nb);
	buffer[len] = '\0';
	(chop_nbr_hex(buffer, nb, len));
}
