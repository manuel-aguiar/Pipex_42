#ifndef PIPEX_H

# define PIPEX_H

#include "get_next_line.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <sys/wait.h>

//# define malloc(x) NULL

# define ERR_PIPE "Pipe error"
# define ERR_FORK "Fork error"
# define ERR_PATH "Binary not in PATH"
# define ERR_DUP "Error in dup"
# define ERR_DUP2 "Error in dup2"
# define ERR_ENV "No PATH on ENV variables"
# define ERR_FIRST_OPEN "Error while opening first file, make sure the first input is a valid file path"
# define ERR_LAST_OPEN "Error while opening last file, make sure the last input is a valid file path"
# define ERR_MALLOC "Malloc failed"
# define ERR_EXEC "Execution failed, check path and/or cmd"
# define ERR_CMD "Cmd failed to launch, check flags and system resources"
# define ERR_NOOBS "Potato"

# define TMPFILE "tmp_BS"

typedef unsigned long	t_ulong;
typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;
typedef const char		t_cchar;

typedef struct s_pipex
{
    char **env;
    char **path;
    int pipefd[2];
    int input;
    int output;
    int is_parent;
    int here_doc;
    char *tmp_name;
} t_pipex;



int error_msg(char *cmd, char *str);
void error_msg_exit(char *cmd, char *str);

int join_path_bin(char **full_path, char *path, char *bin);



/* libft functions */
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(t_cchar *s1, t_cchar *s2, size_t n);
char	**ft_split(t_cchar *s, char c);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void    ft_putstr_fd(int fd, char *str);
int     ft_strlen(char *str);
void	*ft_free_set_null(void *ptr);
void 	*ft_free_charmat_null(void *table, void (*del)(void *));


#endif
