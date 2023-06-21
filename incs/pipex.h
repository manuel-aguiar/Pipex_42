/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:36:48 by marvin            #+#    #+#             */
/*   Updated: 2023/06/21 22:58:13 by mmaria-d         ###   ########.fr       */
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

# include "libft.h"

//# define malloc(x) NULL

# define ERR_PIPE "Pipe error"
# define ERR_FORK "Fork error"
# define ERR_PATH "Binary not in PATH"
# define ERR_DUP "Error in dup"
# define ERR_DUP2 "Error in dup2"
# define ERR_ENV "No PATH on ENV variables"
# define ERR_FIRST_OPEN "Error while opening first file, make sure the \
first input is a valid file path"
# define ERR_LAST_OPEN "Error while opening last file, make sure the \
last input is a valid file path"
# define ERR_MALLOC "Malloc failed"
# define ERR_EXEC "Execution failed, check path and/or cmd"
# define ERR_CMD "Cmd failed to launch, check flags and system resources"
# define ERR_NOOBS "Bad inputs"

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
int		manage_input(t_pipex *pipex, char **av);
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
int		error_msg(char *cmd, char *str);
void	error_msg_exit(char *cmd, char *str);

#endif
