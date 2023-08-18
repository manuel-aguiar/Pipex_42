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

int	pipe_fork_and_output(t_pipex *pipex, int ac, char **av, int i)
{
	if (i < ac - 2)
	{
		if (pipe(pipex->pipefd) == -1)
			return (perror_msg(ERR_PIPE));
		pipex->output = pipex->pipefd[1];
	}
	else if (i == ac - 2)
	{
		if (pipex->here_doc)
			pipex->output = open(av[i + 1], O_CREAT \
							| O_RDWR | O_APPEND, 0644);
		else
			pipex->output = open(av[i + 1], O_CREAT \
							| O_RDWR | O_TRUNC, 0644);
		if (pipex->output == -1)
			return (perror_msg(av[i + 1]));
	}
	pipex->is_parent = fork();
	if (pipex->is_parent == -1)
		return (perror_msg(ERR_FORK));
	return (1);
}

int	child_process(t_pipex *pipex, char **av, int i)
{
	if (pipex->pipefd[0] != -1)
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
		pipex->input = pipex->pipefd[0];
		pipex->pipefd[0] = -1;
		pipex->pipefd[1] = -1;
	}
	return (1);
}

int	process_execution(t_pipex *pipex, int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac - 1)
	{
		if (pipe_fork_and_output(pipex, ac, av, i))
		{
			if (!pipex->is_parent)
				child_process(pipex, av, i);
			parent_process(pipex);
		}
		else
			return (0);
		i++;
	}
	return (1);
}
