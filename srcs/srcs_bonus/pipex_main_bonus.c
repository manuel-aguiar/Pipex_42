/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:01:39 by marvin            #+#    #+#             */
/*   Updated: 2023/08/16 23:04:32 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	if (ac < 5)
		return (error_msg(ERR_NOOBS));
	else
	{
		if (pipex_solver(--ac, ++av, env))
			return (0);
		else
			return (1);
	}
	return (0);
}
