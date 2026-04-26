/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 09:07:29 by isoulima          #+#    #+#             */
/*   Updated: 2025/12/26 09:10:48 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
ssize_t	convert(const char *str, va_list *args);
ssize_t	ft_putchar(char c);
ssize_t	ft_putstr(char *str);
ssize_t	ft_putnbr(int n);
ssize_t	ft_putptr(void *ptr);
ssize_t	ft_putun(unsigned int n);
ssize_t	ft_puthex(unsigned int n, int index);

#endif
