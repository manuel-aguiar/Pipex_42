/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:01:39 by marvin            #+#    #+#             */
/*   Updated: 2023/08/16 22:08:09 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
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

/*
valgrind --trace-children=yes --track-origins=yes --leak-check=full
--show-leak-kinds=all ./pipex_bonus here_doc tibaria cat cat brah.txt
*/
