/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:11:11 by marvin            #+#    #+#             */
/*   Updated: 2023/06/01 12:11:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	setup_pipex_st(t_pipex *pipex, char **env)
{
	int		i;
	char	**folders;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	if (!env[i])
		return (error_msg(NULL, ERR_PATH));
	folders = ft_split(&env[i][5], ':');
	if (folders)
		pipex->path = folders;
	else
		return (error_msg(NULL, ERR_MALLOC));
	pipex->env = env;
	pipex->input = -1;
	pipex->output = -1;
	pipex->is_parent = -1;
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	pipex->here_doc = 0;
	pipex->tmp_name = NULL;
	return (1);
}

int	destroy_pipex_st(t_pipex *pipex)
{
	ft_free_charmat_null(&(pipex->path), &free);
	ft_free_set_null(&(pipex->tmp_name));
	return (1);
}
