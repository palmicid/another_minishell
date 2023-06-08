/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:56:03 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/08 12:50:18 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKEND_H
# define BACKEND_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>
# include "../lib/libft/libft.h"

# define DEBUG 1

typedef enum e_filetype
{
	STDIN,
	STDOUT,
	INFILE,
	HEREDOC,
	OUTFILE,
	APPEND,
	PIPE,
}	t_filetype;

typedef enum e_error
{
	PIPE_ERROR,
	FORK_ERROR,
	CMD_ERROR,
	FILE_ERROR,
	ACCESS_ERROR,
	OPEN_ERROR,
	CLOSE_ERROR,
	EXEC_ERROR,
	ALLOC_ERROR,
}	t_error;

typedef struct s_listcmd
{
	char				**cmd;
	struct s_listcmd	*next;
}	t_listcmd;
typedef struct s_fileset
{
	char		*name;
	int			fd;
	t_filetype	type;
}	t_fileset;

typedef struct s_exec
{
	pid_t	pid;
	int		pipefd[2];
	t_list	*cmdlst;
	char	**cmdarr;
	t_list	*infile;
	t_list	*outfile;
}	t_exec;

typedef struct s_parser
{
	char	**envp;
	char	**path;
	t_list	*exec;
	int		status;
}	t_parser;

// debugger.c
void		print_debug(int argc, ...);

// parser_utils.c
/* ****************************************************************************
initializes the t_parser struct
**************************************************************************** */
t_parser	*ps_init(char **envp);
/* ****************************************************************************
get PATH from envp
**************************************************************************** */
char		**ps_getpath(char **envp);
/* ****************************************************************************
free t_exec struct
**************************************************************************** */
void	*ps_free(void *ps);
void	ps_free2(void *ps);

// exec_utils.c
/* ****************************************************************************
initializes the t_exec struct
**************************************************************************** */
t_exec		*exec_init(void);
/* ****************************************************************************
free t_parser struct
**************************************************************************** */
void		*exec_free(void *exec);
void		exec_free2(void *exec);

// fs_utils.c
/* ****************************************************************************
initializes the t_fileset struct
**************************************************************************** */
t_fileset	*fs_init(char *name, int fd, t_filetype type);
/* ****************************************************************************
free t_fileset struct
**************************************************************************** */
void		*fs_free(void *ptr);
void		fs_free2(void *ptr);
/* ****************************************************************************
check access for all t_fileset in the list
- return 0 if all access is ok, otherwise return errno
- set fd to the file descriptor of the last t_fileset in the list
**************************************************************************** */
int			fs_check(t_list *fslst, int *fd);
/* ****************************************************************************
close all non-pipe non-std fd in the list that is not intended to leave open
**************************************************************************** */
void		fs_close(t_list *fslst, int ignore[2]);

// file_utils.c
/* ****************************************************************************
check file access, open it and set fd to the file descriptor
**************************************************************************** */
int			file_open(t_fileset *fs);
/* ****************************************************************************
create a heredoc file and set fd to the file descriptor
**************************************************************************** */
int			heredoc_open(t_fileset *fs);
/* ****************************************************************************
close fd and set to INT_MIN
**************************************************************************** */
void		file_close(int *fd);

// arr_utils.c
/* ****************************************************************************
convert t_list to char **arr
**************************************************************************** */
char		**lst2arr(t_list *lst);
/* ****************************************************************************
free char **arr
**************************************************************************** */
char		**ft_arrclear(char **arr);

// malloc_utils.c
/* ****************************************************************************
free the pointer and return null to the pointer
**************************************************************************** */
void		*ft_free(void *ptr);

// parser.c
/* ****************************************************************************
parses the command line arguments
**************************************************************************** */
t_parser	*parser(t_listcmd *cmdlst, char **envp);
/* ****************************************************************************
parses t_listcmd to t_exec
**************************************************************************** */
t_exec		*parse2exec(t_listcmd *lc);
/* ****************************************************************************
parses the command line arguments to t_fileset
**************************************************************************** */
void		parse2fs(char **str, int i, t_exec *exec);
/* ****************************************************************************
redirect to pipe for all processes
**************************************************************************** */
void		parser_addpipe(t_list *ptr, t_parser *ps);

// executor.c
/* ****************************************************************************
executes the command line arguments
**************************************************************************** */
int			executor(t_listcmd *lc, char **envp);
/* ****************************************************************************
forks the processes and executes the command line arguments
**************************************************************************** */
int			executor_fork(t_parser *ps);
int			executor_wait(t_parser *ps);

// executor_utils.c
/* ****************************************************************************
free the t_parser struct and return the status
**************************************************************************** */
int			executor_free(t_parser *ps);
/* ****************************************************************************
handle the error in executor
**************************************************************************** */
int			executor_error(t_parser *ps, char *msg, t_error err, int errnum);

// pseudopipex.c
/* ****************************************************************************
execute the command line arguments in t_exec
**************************************************************************** */
int			pipex_exec(t_exec *exec, t_parser *ps);
/* ****************************************************************************
redirect fd to stdin and stdout
**************************************************************************** */
void		dup_close(int *fd);
/* ****************************************************************************
close all the unnecessary fd, leaving ignore'th pipe fd open
**************************************************************************** */
void		pipex_close(t_parser *ps, int ig0, int ig1);

// pseudopipex_cmd.c
/* ****************************************************************************
find $PATH environment that contains the command
**************************************************************************** */
int			cmd_findpath(char **cmd, t_parser *ps);
/* ****************************************************************************
prepend the first string with <s2/>
**************************************************************************** */
char		*ft_strprepend(char *s1, char *s2);
int			cmdcheck_path(char **cmd, t_parser *ps);
int			cmdcheck_notpath(char **cmd, t_parser *ps);

#endif
