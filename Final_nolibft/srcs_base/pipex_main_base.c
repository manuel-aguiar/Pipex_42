/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:01:39 by marvin            #+#    #+#             */
/*   Updated: 2023/06/06 18:57:13 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	if (ac != 5 || !ft_strncmp("here_doc", av[1], 8))
		return (error_msg(NULL, ERR_NOOBS));
	else
	{
		if (pipex_solver(--ac, ++av, env))
			return (0);
		else
			return (1);
	}
	return (0);
}
