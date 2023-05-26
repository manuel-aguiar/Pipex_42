/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:28:25 by manuel            #+#    #+#             */
/*   Updated: 2023/04/18 17:53:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int error_msg(char *cmd, char *str)
{
    
    if (str)
        ft_putstr_fd(STDERR_FILENO, str);
    if (cmd)
    {
        ft_putstr_fd(STDERR_FILENO, ": ");
        ft_putstr_fd(STDERR_FILENO, cmd);
    }
    if (str || cmd)
        ft_putstr_fd(STDERR_FILENO, "\n");
    return (0);
}

void error_msg_exit(char *cmd, char *str)
{
    
    if (str)
        ft_putstr_fd(STDERR_FILENO, str);
    if (cmd)
    {
        ft_putstr_fd(STDERR_FILENO, ": ");
        ft_putstr_fd(STDERR_FILENO, cmd);
    }
    if (str || cmd)
        ft_putstr_fd(STDERR_FILENO, "\n");
    exit(EXIT_FAILURE);
}

int	ft_strncmp(t_cchar *s1, t_cchar *s2, size_t n)
{
	t_cchar	*str1;
	t_cchar	*str2;

	str1 = (t_cchar *)s1;
	str2 = (t_cchar *)s2;
	if (n == 0)
		return (0);
	while (--n && (*str1 || *str2) && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

char	*ft_strdup(char *s)
{
	int		len;
	char	*dest;

	len = ft_strlen(s);
	dest = malloc(sizeof(*dest) * (len + 1));
	if (dest)
	{
		ft_memcpy(dest, s, len);
		dest[len] = '\0';
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new = malloc(sizeof(*new) * (len_s1 + len_s2 + 1));
	if (new)
	{
		ft_memcpy(new, s1, len_s1);
		ft_memcpy(&new[len_s1], s2, len_s2);
		new[len_s1 + len_s2] = '\0';
	}
	return (new);
}

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    ft_putstr_fd(int fd, char *str)
{
    write(fd, str, ft_strlen(str));
}

void	*ft_free_set_null(void *ptr)
{
	t_uchar	**to_free;

	to_free = (unsigned char **)ptr;
	free(*to_free);
	*to_free = NULL;
	return (NULL);
}

void	*ft_free_charmat_null(void *table, void (*del)(void *))
{
	int		i;
	char	**split;

	split = *((char ***)table);
	if (!split || !*split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		del(split[i]);
		split[i] = NULL;
		i++;
	}
	return (ft_free_set_null(table));
}

