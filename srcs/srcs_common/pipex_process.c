/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:34:23 by marvin            #+#    #+#             */
/*   Updated: 2023/06/01 12:34:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipe_and_fork(t_pipex *pipex, int ac, int i)
{
	if (i < ac - 2)
	{
		if (pipe(pipex->pipefd) == -1)
			return (error_msg(NULL, ERR_PIPE));
	}
	pipex->is_parent = fork();
	if (pipex->is_parent == -1)
		return (error_msg(NULL, ERR_FORK));
	return (1);
}

int	child_process(t_pipex *pipex, char **av, int i)
{
	if (i == 0 && pipex->pipefd[0] != -1)
		close(pipex->pipefd[0]);
	if (dup2(pipex->input, STDIN_FILENO) == -1)
		error_msg_exit(NULL, ERR_DUP2);
	if (dup2(pipex->output, STDOUT_FILENO) == -1)
		error_msg_exit(NULL, ERR_DUP2);
	close(pipex->input);
	close(pipex->output);
	if (!exec_command(pipex, av[i]))
	{
		destroy_pipex_st(pipex);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	parent_process(t_pipex *pipex)
{
	if (pipex->here_doc)
	{
		unlink(pipex->tmp_name);
		ft_free_set_null(&pipex->tmp_name);
		pipex->here_doc = 0;
	}
	close(pipex->input);
	close(pipex->output);
	if (pipex->pipefd[0] != -1)
	{
		pipex->input = dup(pipex->pipefd[0]);
		if (pipex->input == -1)
			return (error_msg(NULL, ERR_DUP));
		close(pipex->pipefd[0]);
	}
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	return (1);
}

int	command_execution(t_pipex *pipex, int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac - 1)
	{
		if (i == ac - 2)
		{
			pipex->output = open(av[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (pipex->output == -1)
				return (error_msg(NULL, ERR_LAST_OPEN));
		}
		if (pipe_and_fork(pipex, ac, i))
		{
			if (i < ac - 2)
				pipex->output = pipex->pipefd[1];
			if (pipex->is_parent == 0)
				child_process(pipex, av, i);
			if (!parent_process(pipex))
				return (0);
		}
		else
			return (0);
		i++;
	}
	return (1);
}
