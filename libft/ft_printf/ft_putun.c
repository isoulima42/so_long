/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 09:07:44 by isoulima          #+#    #+#             */
/*   Updated: 2025/12/26 10:26:04 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_putun(unsigned int n)
{
	unsigned long	nb;
	char			c;
	int				count;

	nb = n;
	count = 0;
	if ((long)nb < 0)
	{
		nb = -nb;
	}
	if (nb > 9)
		count += ft_putun(nb / 10);
	c = (nb % 10) + '0';
	count += ft_putchar(c);
	return (count);
}
