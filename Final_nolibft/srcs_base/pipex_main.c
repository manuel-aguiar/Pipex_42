/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include "pipex.h"

int setup_pipex_st(t_pipex *pipex, char **env)
{
    int i;
	char **folders;
	
	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	if (env[i])
	{
		folders = ft_split(&env[i][5], ':');
		if (folders)
		    pipex->path = folders;
		else
		    return (error_msg(NULL, ERR_MALLOC));
	}
	else
	    return (error_msg(NULL, ERR_PATH));
	pipex->env = env;
	pipex->input = -1;
	pipex->output = -1;
	pipex->is_parent = -1;
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	pipex->here_doc = 0;
	pipex->tmp_name = NULL;
	return (1);
}

int destroy_pipex_st(t_pipex *pipex)
{
    ft_free_charmat_null(&(pipex->path), &free);
	return (1);
}

int join_path_bin(char **full_path, char *path, char *bin)
{
    int     path_len;
    int     bin_len;
    char    *new;
    
    path_len = ft_strlen(path);
    if (path[path_len - 1] == '/')
        path_len--;
    bin_len = ft_strlen(bin);
    new = malloc(sizeof(*new) * (path_len + bin_len + 1 + 1));
    if (!new)
        return (error_msg(NULL, ERR_MALLOC));
    ft_memcpy(new, path, path_len);
    new[path_len] = '/';
    ft_memcpy(&new[path_len + 1], bin, bin_len);
    new[path_len + bin_len + 1] = '\0';
    *full_path = new;
    return (1);
}

/*
int check_command(t_pipex *pipex, char *cmd)
{
    int i;
    char *full_path;
    char **cmd_args;
    
    cmd_args = ft_split(cmd, ' ');
    if (!cmd_args)
        return (error_msg(NULL, ERR_MALLOC));
    i = 0;
	while(pipex->path[i])
	{
	    if (join_path_bin(&full_path, pipex->path[i], cmd_args[0]))
	    {
	        if (access(full_path, F_OK) == 0)
	        {
    		    pipex->cmd = cmd_args;
    		    pipex->cmd_path = full_path;
    		    return (1);
	        }
		    else
		        ft_free_set_null(&full_path);
	    }
	    else
	    {
	        return (error_msg(NULL, ERR_MALLOC));
	    }
		i++;
	}
    ft_free_charmat_null(&cmd_args, &free);
	return (error_msg(cmd, ERR_EXEC));
}*/

int exec_command(t_pipex *pipex, char *cmd)
{
    int i;
    char *full_path;
    char **cmd_args;
    
    cmd_args = ft_split(cmd, ' ');
    if (!cmd_args)
        return (error_msg(NULL, ERR_MALLOC));
    i = 0;
	while(pipex->path[i])
	{
	    if (join_path_bin(&full_path, pipex->path[i++], cmd_args[0]))
	    {
	        if (access(full_path, F_OK) == 0)
	        {
    		    if (execve(full_path, cmd_args, pipex->env) == -1)
    		        break;
	        }
		    else
		        ft_free_set_null(&full_path);
	    }
	    else
	        break;
	}
	ft_free_set_null(&full_path);
    ft_free_charmat_null(&cmd_args, &free);
	return (error_msg(cmd, ERR_EXEC));
}

/*
int check_output(t_pipex *pipex, int ac, char **av, int i)
{
    if (i == ac - 2)
    {
        pipex->output = open(av[i + 1], O_CREAT | O_WRONLY, 0644);
        if (pipex->output == -1)
            return (error_msg(NULL, ERR_LAST_OPEN));
    }
    else
        pipex->output = pipex->pipefd[1];
    return (1);
}*/

int pipe_and_fork(t_pipex *pipex, int ac, int i)
{
    if (i < ac - 2)
    {
        if (pipe(pipex->pipefd) == -1)
            return (error_msg(NULL, ERR_PIPE));
    }
    pipex->is_parent = fork();
    if (pipex->is_parent == -1)
        return (error_msg(NULL, ERR_FORK));
    return (1);
}

int    child_process(t_pipex *pipex, char **av, int i)
{
    if (i == 0 && pipex->pipefd[0] != -1)
        close(pipex->pipefd[0]);
    if (dup2(pipex->input, STDIN_FILENO) == -1)
        error_msg_exit(NULL, ERR_DUP2);
    if (dup2(pipex->output, STDOUT_FILENO) == -1)
        error_msg_exit(NULL, ERR_DUP2);
    close(pipex->input);
    close(pipex->output);
    if (!exec_command(pipex, av[i]))
    {
        destroy_pipex_st(pipex);
        exit(EXIT_FAILURE);
    }
    return (0);
}

/*
//int i;
//char *path;
i = 0;
while (ft_strncmp("PWD=", pipex->env[i], 4))
    i++;
if (join_path_bin(&path, &(pipex->env[i][4]), TMPFILE))
{
    printf("path to free: %s\n", path);
    unlink(path);
}
else
    error_msg(NULL, ERR_MALLOC);
ft_free_set_null(&path);
pipex->here_doc = 0;*/

int    parent_process(t_pipex *pipex)
{
    if (pipex->here_doc)
    {
        unlink(pipex->tmp_name);
        free(pipex->tmp_name);
        pipex->here_doc = 0;
    }
    close(pipex->input);
    close(pipex->output);
    if (pipex->pipefd[0] != -1)
    {
	    pipex->input = dup(pipex->pipefd[0]);
	    if (pipex->input == -1)
	        return (error_msg(NULL, ERR_DUP));
        close(pipex->pipefd[0]);
    }
    pipex->pipefd[0] = -1;
    pipex->pipefd[1] = -1;
    return (1);
}

int command_execution(t_pipex *pipex, int ac, char **av)
{
    int i;
    
    i = 0;
    while (i < ac - 1)
    {
        if (i == ac - 2)
        {
            pipex->output = open(av[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (pipex->output == -1)
                return (error_msg(NULL, ERR_LAST_OPEN));
        }
        if (pipe_and_fork(pipex, ac, i))
        {
            if (i < ac - 2)
                pipex->output = pipex->pipefd[1];
            if (pipex->is_parent == 0)
                child_process(pipex, av, i);
            if(!parent_process(pipex))
                return (0);
        }
        else
            return (0);
        i++;
    }
    return (1);
}

/*i = 0;
    while (ft_strncmp("PWD=", pipex->env[i], 4))
        i++;
    pipex->input = open(&(pipex->env[i][5]), O_TMPFILE | O_RDWR, 0644);*/

void dfs(char *buf, int max, int cur, int *found)
{
    char c;
    
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
            buf[cur + 1] = '\0';
            dfs(buf, max, cur + 1, found);
            if (*found)
                return ;
            buf[cur] = '\0';
            c++;
        }
    }
}

int generate_temp(t_pipex *pipex)
{
    char new[256];
    int max_len;
    int found;
    
    found = 0;
    max_len = sizeof(new);
    *new = '\0';
    dfs(new, max_len, 0, &found);
    pipex->tmp_name = ft_strdup(new);
    if (pipex->tmp_name)
        return (1);
    return (0);
}

int here_doc(t_pipex *pipex, char **av)
{
    int stop;
    char *line;
    int temp;
    
    
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

int manage_input(t_pipex *pipex, char **av)
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

int solver(int ac, char **av, char **env)
{
    t_pipex pipex;
    int     error;
    
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

int main(int ac, char **av, char **env)
{
	if (ac < 4)
	    return (error_msg(NULL, ERR_NOOBS));
	else
	{
	    if (solver(--ac, ++av, env))
	        return (0);
	    else
	        return (1);
	}
	return (0);
}

