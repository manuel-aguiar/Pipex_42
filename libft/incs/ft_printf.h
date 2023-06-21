/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:03:55 by manuel            #+#    #+#             */
/*   Updated: 2023/04/20 16:23:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# define HEXS "0123456789abcdef"
# define HEXB "0123456789ABCDEF"
# define HEXLEN 16
# define FLAGS "cspdiuxX%"
# include <stdarg.h>

# include <unistd.h>    /* DELETE */
# include "ft_string.h"

/* ---- ft_printf.c ---- */
int	ft_printf(const char *str, ...);

#endif
