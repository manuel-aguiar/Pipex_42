/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:32:48 by marvin            #+#    #+#             */
/*   Updated: 2023/06/01 12:32:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	join_path_bin(char **full_path, char *path, char *bin)
{
	int		path_len;
	int		bin_len;
	char	*new;

	path_len = ft_strlen(path);
	if (path[path_len - 1] == '/')
		path_len--;
	bin_len = ft_strlen(bin);
	new = malloc(sizeof(*new) * (path_len + bin_len + 1 + 1));
	if (!new)
	{
		*full_path = new;
		return (perror_msg(ERR_MALLOC));
	}
	ft_memcpy(new, path, path_len);
	new[path_len] = '/';
	ft_memcpy(&new[path_len + 1], bin, bin_len);
	new[path_len + bin_len + 1] = '\0';
	*full_path = new;
	return (1);
}

int	exec_cmd_with_path(t_pipex *pipex, char ***args)
{
	char	**cmd_args;

	cmd_args = *args;
	if (access(cmd_args[0], F_OK))
		return (perror_msg(cmd_args[0]));
	else if (execve(cmd_args[0], cmd_args, pipex->env) == -1)
		return (perror_msg(cmd_args[0]));
	return (1);
}

int	exec_cmd_search_path(t_pipex *pipex, char ***args)
{
	int		i;
	char	*full_path;
	char	**cmd_args;

	cmd_args = *args;
	i = 0;
	while (pipex->path[i])
	{
		if (!join_path_bin(&full_path, pipex->path[i++], cmd_args[0]))
			return (0);
		if (access(full_path, F_OK) == 0)
		{
			if (execve(full_path, cmd_args, pipex->env) == -1)
			{
				perror(cmd_args[0]);
				ft_free_set_null(&full_path);
				return (0);
			}
		}
		else
			ft_free_set_null(&full_path);
	}
	return (0 & ft_printf_fd(STDERR_FILENO, "%s: %s\n", \
			ERR_CMD, cmd_args[0]));
}

int	exec_command(t_pipex *pipex, char *cmd)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		return (perror_msg(ERR_MALLOC));
	if (ft_strrchr(cmd_args[0], '/'))
		exec_cmd_with_path(pipex, &cmd_args);
	else
		exec_cmd_search_path(pipex, &cmd_args);
	ft_free_charmat_null(&cmd_args, &free);
	return (0);
}
