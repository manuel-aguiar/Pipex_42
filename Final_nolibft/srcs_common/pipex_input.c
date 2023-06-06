/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:21:26 by marvin            #+#    #+#             */
/*   Updated: 2023/06/01 12:21:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(t_pipex *pipex, char **av)
{
	int		stop;
	char	*line;
	int		temp;

	temp = open(pipex->tmp_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (temp == -1)
		return (error_msg(NULL, ERR_FIRST_OPEN));
	stop = 0;
	line = (char *)1;
	while (line && !stop)
	{
		line = get_next_line(0);
		if (line)
		{
			ft_putstr_fd(temp, line);
			if (!ft_strncmp(av[1], line, ft_strlen(av[1])))
				stop = 1;
			free(line);
		}
	}
	close(temp);
	pipex->input = open(pipex->tmp_name, O_RDONLY);
	if (pipex->input == -1)
		return (error_msg(NULL, ERR_FIRST_OPEN));
	return (1);
}

int	manage_input(t_pipex *pipex, char **av)
{
	if (!ft_strncmp("here_doc", av[0], 8) && ft_strlen(av[0]) == 8)
		pipex->here_doc = 1;
	if (!pipex->here_doc)
	{
		pipex->input = open(av[0], O_RDONLY);
		if (pipex->input == -1)
			return (error_msg(NULL, ERR_FIRST_OPEN));
	}
	else
	{
		if (generate_temp(pipex))
			return (here_doc(pipex, av));
		else
			return (error_msg(NULL, ERR_MALLOC));
	}
	return (1);
}

int	pipex_solver(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int		error;

	error = 1;
	if (!setup_pipex_st(&pipex, env))
		return (0);
	if (!manage_input(&pipex, av))
		error = 0;
	av += pipex.here_doc;
	ac -= pipex.here_doc;
	if (error)
	{
		if (!command_execution(&pipex, --ac, ++av))
			error = 0;
	}
	destroy_pipex_st(&pipex);
	while (ac-- - 1 > 0)
		wait(NULL);
	return (error);
}
