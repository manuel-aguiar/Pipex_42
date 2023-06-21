/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:03:55 by manuel            #+#    #+#             */
/*   Updated: 2023/04/20 16:23:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ---- print_pxX.c ---- */
int	putcountaddr(void *address);
int	putcounthex(unsigned int nb, char *base);

/* ---- print_csdiu_perc.c ---- */
int	putcountint(int nb);
int	putcountunint(unsigned int nb);
int	putcountstr(char *str);
int	putcountchar(char c);

static int	flagcheck(char c, char *flags, va_list ptr)
{
	if (!flags)
		return (0);
	while (*flags)
	{
		if (c == *flags)
			return (1);
		flags++;
	}
	va_arg(ptr, int);
	return (0);
}

static int	printformat(va_list ptr, char flag)
{
	if (!flagcheck(flag, FLAGS, ptr))
		return (0);
	if (flag == 'c')
		return (putcountchar(va_arg(ptr, int)));
	if (flag == 's')
		return (putcountstr(va_arg(ptr, char *)));
	if (flag == 'p')
		return (putcountaddr(va_arg(ptr, void *)));
	if (flag == 'd' || flag == 'i')
		return (putcountint(va_arg(ptr, int)));
	if (flag == 'u')
		return (putcountunint(va_arg(ptr, unsigned int)));
	if (flag == 'x')
		return (putcounthex(va_arg(ptr, unsigned int), HEXS));
	if (flag == 'X')
		return (putcounthex(va_arg(ptr, unsigned int), HEXB));
	if (flag == '%')
		return (putcountchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	int		i;

	i = 0;
	va_start(ptr, str);
	while (*str)
	{
		if (*str != '%')
		{
			write(1, str, 1);
			i++;
		}
		else
		{
			i += printformat(ptr, *(str + 1));
			str++;
		}
		str++;
	}
	va_end(ptr);
	return (i);
}
