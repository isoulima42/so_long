/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 09:07:39 by isoulima          #+#    #+#             */
/*   Updated: 2025/12/26 11:07:50 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_ptr(unsigned long long nb, char *base, int *count)
{
	if (nb >= 16)
		ft_putnbr_ptr(nb / 16, base, count);
	*count += write(1, &base[nb % 16], 1);
}

ssize_t	ft_putptr(void *ptr)
{
	unsigned long long	address;
	char				*base;
	int					count;

	address = (unsigned long long)ptr;
	base = "0123456789abcdef";
	count = write(1, "0x", 2);
	if (address == 0)
		return (count + write(1, "0", 1));
	ft_putnbr_ptr(address, base, &count);
	return (count);
}
