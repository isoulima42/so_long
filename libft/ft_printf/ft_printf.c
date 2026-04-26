/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 09:07:27 by isoulima          #+#    #+#             */
/*   Updated: 2025/12/26 10:15:55 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	convert(const char *str, va_list *args)
{
	if (*(str + 1) == 'c')
		return (ft_putchar(va_arg(*args, int)));
	else if (*(str + 1) == 's')
		return (ft_putstr((char *)va_arg(*args, char *)));
	else if (*(str + 1) == 'd' || *(str + 1) == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	else if (*(str + 1) == 'u')
		return (ft_putun(va_arg(*args, unsigned int)));
	else if (*(str + 1) == 'x')
		return (ft_puthex(va_arg(*args, unsigned int), 1));
	else if (*(str + 1) == 'X')
		return (ft_puthex(va_arg(*args, unsigned int), 0));
	else if (*(str + 1) == '%')
		return (ft_putchar('%'));
	else if (*(str + 1) == 'p')
		return (ft_putptr(va_arg(*args, void *)));
	else if (*(str + 1) == '\0')
		return (0);
	else
		return (-1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
			count += convert(str + i++, &args);
		else
		{
			ft_putchar(str[i]);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
