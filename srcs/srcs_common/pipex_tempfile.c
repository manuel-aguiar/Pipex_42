/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tempfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:14:00 by marvin            #+#    #+#             */
/*   Updated: 2023/06/01 12:14:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	dfs(char *buf, int max, int cur, int *found)
{
	char	c;

	if (cur == max)
		return ;
	if (!*found && *buf && access(buf, F_OK) != 0)
	{
		*found = 1;
		return ;
	}
	if (*found)
		return ;
	else
	{
		c = 'a';
		while (c <= 'z')
		{
			buf[cur] = c;
			dfs(buf, max, cur + 1, found);
			if (*found)
				return ;
			buf[cur] = '\0';
			c++;
		}
	}
}

int	generate_temp(t_pipex *pipex)
{
	char	new[256];
	int		found;

	found = 0;
	ft_memset(new, '\0', sizeof(new));
	dfs(new, sizeof(new), 0, &found);
	pipex->tmp_name = ft_strdup(new);
	if (pipex->tmp_name)
		return (1);
	return (0);
}
