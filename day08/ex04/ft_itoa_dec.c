/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_dec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:44:16 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/24 10:47:14 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATmega.h"

static char	*chop_nbr_dec(char *buffer, uint16_t nb, uint16_t len)
{
	char	base[17] = "0123456789";
	while (nb / 10)
	{
		--len;
		buffer[len] = base[nb % 10];
		nb = nb / 10;
	}
	buffer[len - 1] = base[nb % 10];
	return (buffer);
}

static uint16_t	ft_getlen_dec(uint16_t nb)
{
	uint16_t	len;

	len = 1;
	while (nb / 10)
	{
		nb = nb / 10;
		++len;
	}
	return (len);
}

void	ft_itoa_dec(uint16_t nb, char *buffer)
{
	uint16_t	len;
	char		*str;

	len = ft_getlen_dec(nb);
	buffer[len] = '\0';
	(chop_nbr_dec(buffer, nb, len));
}
