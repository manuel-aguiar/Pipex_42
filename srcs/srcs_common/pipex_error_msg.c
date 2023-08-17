/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:04:16 by marvin            #+#    #+#             */
/*   Updated: 2023/06/01 12:04:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	perror_msg(char *text)
{
	perror(text);
	return (0);
}

int	error_msg(char *text)
{
	ft_putstr_fd(text, STDERR_FILENO);
	return (0);
}

void	perror_child_exit(t_pipex *pipex, char *text, int close_io)
{
	if (text)
		perror(text);
	if (close_io == 1)
	{
		close(pipex->input);
		close(pipex->output);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	destroy_pipex_st(pipex);
	exit(EXIT_FAILURE);
}
