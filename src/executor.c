/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:14:24 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/14 08:39:55 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	executor(t_listcmd *lc, char **envp)
{
	t_parser	*ps;
	int			status;

	ps = parser(lc, envp);
	if (!ps)
		return (ENOMEM); // needs fix when error is done
	status = executor_fork(ps);
	if (status != 0)
		return (status); // needs fix when error is done
	pipex_close(ps, 0, 1);
	status = executor_wait(ps);
	ps_free(ps);
	return (status);
}

int	executor_fork(t_parser *ps)
{
	t_list	*exec;
	t_exec	*ex;
	int		firetruck;

	exec = ps->exec;
	while (exec)
	{
		ex = exec->content;
		ex->pid = fork();
		if (ex->pid == -1)
			return (errno);
		else if (ex->pid == 0)
		{
			firetruck = pipex_exec(exec->content, ps);
			exit(firetruck);
		}
		else
			exec = exec->next;
	}
	return (0);
}

int	executor_wait(t_parser *ps)
{
	t_list	*exec;
	t_exec	*ex;
	int		status;

	exec = ps->exec;
	while (exec)
	{
		ex = exec->content;
		waitpid(ex->pid, &status, 0);
		exec = exec->next;
	}
	return (status);
}
