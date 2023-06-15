/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:18:15 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 09:53:54 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <limits.h>
# include <sys/signal.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include "bltin.h"

# define DEBUG 0

typedef struct s_data
{
	pid_t				pid;
	char				**env;
	int					exit_stat;
}						t_data;

extern char		**environ;

/*
typedef struct s_listcmd
{
	char			**cmd;
	struct s_listcmd	*next;
}					t_listcmd;
*/
typedef struct s_c
{
	int	st;
	int	i;
	int	j;
}		t_c;

// int stst --> 2 = doubleQ " " , 1 = single ' ', 0 non
// use before split with pipe
typedef struct s_strcut
{
	char			*str;
	int				stat;
	struct s_strcut	*next;
}					t_strcut;

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

// minishell
int			process(char *strcmd, t_data *data);
void		soloexit(t_listcmd *cmdlist, t_data *data);

// sig_handle
void		sig_int_handler(int sig);
void		signal_handling(void);
void		sig_int_handler_noredis(int sig);
void		signal_int_handling(int mode);

// env
int			init_environ(t_data *data);
int			end_environ(t_data *data);

// parser_1 - main split + split long list to cmd
t_listcmd	*str_split(char *str, t_data *data);

// parser_2 - quote split and add stat q or nonq
t_strcut	*qsp_split(char *str);

// parser_3 - split meta char | < << >> >
t_strcut	*meta_split(t_strcut *head);

// parser_4 - remove quote
t_strcut	*remove_q_xpand(t_strcut *head, t_data *data);

// parser_5 - expand
void		expand_var(t_strcut *tmp, t_data *data);

// parser_6 - join str from list
void		lst_strjoin(t_strcut *current, t_strcut **tmp);

// utils_1
t_strcut	*free_strcutlist(t_strcut **list);
t_strcut	*free_strcut(t_strcut *tofree);
int			find_charpos(char *str, char c);
t_strcut	*lastlist_strcut(t_strcut *list);
int			cont_char(char *str, int i, char c);

// ------ TEST
void		test_print(t_listcmd *head);
// void		test_printstrcut(t_strcut *fwd);
// void		test_printonestrcut(t_strcut *cur);

// utils_2
int			find_pair(char *str, int i);
int			count_liststrcut(t_strcut *list);
int			ft_isspace(int c);
int			count_samechar(char *str, int pos);
int			find_metapos(char *str);

// utils_3
int			add_metastat(char *str);
t_strcut	*search_liststrcut(t_strcut *head, t_strcut *now);
t_strcut	*new_nowsepmeta(t_strcut *tmphd);
t_strcut	*cx_meta_valid(t_strcut *head);
void		restat_normal(t_strcut *head);

// utils_4
int			find_q_doll(char *str);
void		set_error(t_strcut *cur);
void		remove_q(t_strcut *head);
int			next_i_qsplit(char *str, int i);
t_listcmd	*free_cmdlist(t_listcmd *lstcmd);

// utils_5
t_strcut	*inside_cxmetavalid(t_strcut **head, char *str);
t_strcut	*createnew_strcut(void);
t_listcmd	*createnew_lstcmd(void);
t_c			*create_countptr(void);
// err_msg
void		err_redirpipe(char *str);
void		err_q_nopair(void);
void		err_redir(void);

// execute
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
void		*ps_free(void *ps);
void		ps_free2(void *ps);

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
int			fs_check(t_list *fslst, int *fd, t_parser *ps);
/* ****************************************************************************
close all non-pipe non-std fd in the list that is not intended to leave open
**************************************************************************** */
void		fs_close(t_list *fslst, int ignore[2]);

// file_utils.c
/* ****************************************************************************
check file access, open it and set fd to the file descriptor
**************************************************************************** */
int			file_open(t_fileset *fs, t_parser *ps);
/* ****************************************************************************
create a heredoc file and set fd to the file descriptor
**************************************************************************** */
int			heredoc_open(t_fileset *fs, t_parser *ps);
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
/* ****************************************************************************
execute builtin commands and exit
**************************************************************************** */
int			execve_builtin(t_exec *exec, t_parser *ps, int *stat);

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

// built_in
int			mini_echo(char **strarr);
int			mini_cd(char **strarr);
int			mini_pwd(char **strarr);
int			mini_export(char **strarr);
int			mini_unset(char **strarr);
int			mini_env(char **strarr);
int			mini_exit(char **strarr);

int			find_pos_env(char *tofind);
char		*getvarname(char *str);
char		**sp_splitndup(char **dst, char **src, int n);
int			cx_validvar(char *name);
int			free_reterr_export(char **ptr);
void		bltin_err_msg(char *str);
void		bltin_exiterr_msg(char *str);

#endif
