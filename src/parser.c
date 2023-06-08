/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:56:41 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/08 12:07:36 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

t_parser	*parser(t_listcmd *lc, char **envp)
{
	t_parser	*ps;
	t_exec		*exec;
	t_listcmd	*ptr;
	int			sz;

	ps = ps_init(envp);
	if (!ps)
		executor_error(ps, "malloc", ALLOC_ERROR, errno);
	ptr = lc;
	while (ptr)
	{
		sz = ft_lstsize(ps->exec);
		exec = parse2exec(ptr);
		if (!exec)
			executor_error(ps, "malloc", ALLOC_ERROR, errno);
		ft_lstadd_back(&ps->exec, ft_lstnew(exec));
		if (sz + 1 != ft_lstsize(ps->exec))
			executor_error(ps, "malloc", ALLOC_ERROR, errno);
		ptr = ptr->next;
	}
	parser_addpipe(ps->exec, ps);
	return (ps);
}

t_exec	*parse2exec(t_listcmd *lc) //check malloc error
{
	t_exec		*exec;
	char		*str;
	int			i;

	exec = exec_init();
	if (!exec)
		return (NULL);
	i = -1;
	while (lc->cmd[++i])
	{
		str = lc->cmd[i];
		print_debug(2, "parsing: ", str);
		if (ft_strncmp(str, ">>", 3) == 0 || ft_strncmp(str, "<<", 3) == 0
			|| ft_strncmp(str, "<", 2) == 0 || ft_strncmp(str, ">", 2) == 0)
			parse2fs(lc->cmd, i++, exec);
		else
			ft_lstadd_back(&exec->cmdlst, ft_lstnew(ft_strdup(str)));
	}
	exec->cmdarr = lst2arr(exec->cmdlst);
	return (exec);
}

void	parse2fs(char **str, int i, t_exec *exec)
{
	if (ft_strncmp(str[i], "<", 2) == 0)
	{
		ft_lstadd_back(&exec->infile,
		ft_lstnew(fs_init(str[i + 1], INT_MIN, INFILE)));
	}
	if (ft_strncmp(str[i], "<<", 3) == 0)
	{
		ft_lstadd_back(&exec->infile,
		ft_lstnew(fs_init(str[i + 1], INT_MIN, HEREDOC)));
	}
	if (ft_strncmp(str[i], ">", 2) == 0)
	{
		ft_lstadd_back(&exec->outfile,
		ft_lstnew(fs_init(str[i + 1], INT_MIN, OUTFILE)));
	}
	if (ft_strncmp(str[i], ">>", 3) == 0)
	{
		ft_lstadd_back(&exec->outfile,
		ft_lstnew(fs_init(str[i + 1], INT_MIN, APPEND)));
	}
}

void	parser_addpipe(t_list *ptr, t_parser *ps)
{
	int		prevpipe;
	t_exec	*exec;

	while (ptr->next != NULL)
	{
		exec = ptr->content;
		prevpipe = exec->pipefd[0];
		if (exec->outfile == NULL)
		{
			ft_lstadd_back(&exec->outfile,
			ft_lstnew(fs_init("outpipe", exec->pipefd[1], PIPE)));
			if (exec->outfile == NULL)
				executor_error(ps, "malloc", ALLOC_ERROR, errno);
			print_debug(2, "redirect outfile to fd", ft_itoa(exec->pipefd[1]));
		}
		ptr = ptr->next;
		exec = ptr->content;
		if (exec->infile == NULL)
		{
			ft_lstadd_back(&exec->infile,
			ft_lstnew(fs_init("inpipe", prevpipe, PIPE)));
			if (exec->infile == NULL)
				executor_error(ps, "malloc", ALLOC_ERROR, errno);
			print_debug(2, "redirect infile to fd", ft_itoa(prevpipe));
		}
	}
}

int	parser_error(t_parser *ps, char *msg, t_error err, int errnum)
{
	ft_putstr_fd("minishell: ", 2);
	if (err == CMD_ERROR || err == FILE_ERROR || err == ACCESS_ERROR)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (err == CMD_ERROR)
		ft_putendl_fd("command not found", 2);
	else
		ft_putendl_fd(strerror(errnum), 2);
	ps_free(ps);
	exit(errnum);
}
