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

int	error_msg(char *cmd, char *str)
{
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
	}
	if (str || cmd)
		ft_putstr_fd("\n", STDERR_FILENO);
	return (0);
}

void	error_msg_exit(char *cmd, char *str)
{
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
	}
	if (str || cmd)
		ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
