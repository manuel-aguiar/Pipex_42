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
			return (error_msg(ERR_PIPE));
	}
	pipex->is_parent = fork();
	if (pipex->is_parent == -1)
		return (error_msg(ERR_FORK));
	return (1);
}

int	child_process(t_pipex *pipex, char **av, int i)
{
	if (i == 0 && pipex->pipefd[0] != -1)
		close(pipex->pipefd[0]);
	if (dup2(pipex->input, STDIN_FILENO) == -1 \
	|| dup2(pipex->output, STDOUT_FILENO) == -1)
		perror_child_exit(pipex, ERR_DUP2, TRUE);
	close(pipex->input);
	close(pipex->output);
	if (!exec_command(pipex, av[i]))
		perror_child_exit(pipex, NULL, FALSE);
	return (0);
}

int	parent_process(t_pipex *pipex)
{
	if (pipex->here_doc && pipex->tmp_name)
	{
		unlink(pipex->tmp_name);
		ft_free_set_null(&pipex->tmp_name);
	}
	close(pipex->input);
	close(pipex->output);
	if (pipex->pipefd[0] != -1)
	{
		pipex->input = dup(pipex->pipefd[0]);
		if (pipex->input == -1)
			perror_msg(ERR_DUP);
		close(pipex->pipefd[0]);
		if (pipex->input == -1)
			return (0);
	}
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	return (1);
}

int	output_file(t_pipex *pipex, char **av, int index)
{
	if (pipex->here_doc)
		pipex->output = open(av[index + 1], O_CREAT \
						| O_WRONLY | O_APPEND, 0644);
	else
		pipex->output = open(av[index + 1], O_CREAT \
						| O_WRONLY | O_TRUNC, 0644);
	if (pipex->output == -1)
		return (perror_msg(av[index + 1]));
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
			if (!output_file(pipex, av, i))
				return (0);
		}
		if (pipe_and_fork(pipex, ac, i))
		{
			if (i < ac - 2)
				pipex->output = pipex->pipefd[1];
			if (!pipex->is_parent)
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
