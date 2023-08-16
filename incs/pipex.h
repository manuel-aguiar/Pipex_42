/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:36:48 by marvin            #+#    #+#             */
/*   Updated: 2023/08/16 23:15:36 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>

# include "libft.h"

//# define malloc(x) NULL

# define ERR_PIPE "Pipe"
# define ERR_FORK "Fork"
# define ERR_PATH "Binary not in PATH"
# define ERR_DUP "dup"
# define ERR_DUP2 "dup2"
# define ERR_ENV "No PATH on ENV variables"
# define ERR_MALLOC "Malloc"
# define ERR_NOOBS "pipex: Wrond number of Inputs\n"

# define TMPFILE "tmp_BS"

typedef struct s_pipex
{
	char	**env;
	char	**path;
	int		pipefd[2];
	int		input;
	int		output;
	int		is_parent;
	int		here_doc;
	char	*tmp_name;
}	t_pipex;

/*pipex_struct.c*/
int		setup_pipex_st(t_pipex *pipex, char **env);
int		destroy_pipex_st(t_pipex *pipex);

/*pipex_input.c*/
int		here_doc(t_pipex *pipex, char **av);
int		manage_input(t_pipex *pipex, char **av, int ac);
int		pipex_solver(int ac, char **av, char **env);

/*pipex_tempfile.c*/
int		generate_temp(t_pipex *pipex);

/*pipex_process*/
int		pipe_and_fork(t_pipex *pipex, int ac, int i);
int		child_process(t_pipex *pipex, char **av, int i);
int		parent_process(t_pipex *pipex);
int		command_execution(t_pipex *pipex, int ac, char **av);

/*pipex_exec.c*/
int		join_path_bin(char **full_path, char *path, char *bin);
int		exec_command(t_pipex *pipex, char *cmd);

/*pipex_error_msg.c*/
int		error_msg(char *text);
int		perror_msg(char *text);
void	error_msg_exit(t_pipex *pipex, char *cmd, char *str);

#endif
