/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_csdiu_perc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:03:55 by manuel            #+#    #+#             */
/*   Updated: 2023/04/20 16:23:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putcountint(int nb)
{
	char	str[11];
	char	print;
	int		i;
	char	sign;

	sign = 1;
	i = sizeof(str);
	if (nb < 0)
		sign = -1;
	if (nb == 0)
		str[--i] = '0';
	while (nb != 0)
	{
		print = nb % 10;
		if (print < 0)
			print *= -1;
		str[--i] = print + '0';
		nb /= 10;
	}
	if (sign == -1)
		str[--i] = '-';
	return (write(1, &str[i], sizeof(str) - i));
}

int	putcountunint(unsigned int nb)
{
	char	str[11];
	int		i;

	i = sizeof(str);
	if (nb == 0)
		str[--i] = '0';
	while (nb != 0)
	{
		str[--i] = (nb % 10) + '0';
		nb /= 10;
	}
	return (write(1, &str[i], sizeof(str) - i));
}

int	putcountstr(char *str)
{
	if (!str)
		return (putcountstr("(null)"));
	return (write(1, str, ft_strlen(str)));
}

int	putcountchar(char c)
{
	return (write(1, &c, 1));
}
