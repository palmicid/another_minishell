/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudopipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:05:07 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/07 17:46:04 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	pipex_exec(t_exec *exec, t_parser *ps)
{
	int	ignore[2];
	int	status;

	status = fs_check(exec->infile, &ignore[0]);
	if (status != 0)
		return (status); //error
	status = fs_check(exec->outfile, &ignore[1]);
	if (status != 0)
		return (status); //error
	status = cmd_findpath(exec->cmdarr, ps);
	if (status != 0)
		return (status); //error
	dup_close(ignore);
	execve(exec->cmdarr[0], exec->cmdarr, ps->envp);
	return (0);
}

void	dup_close(int fd[2])
{
	if (fd[0] > 2)
	{
		dup2(fd[0], STDIN_FILENO);
		file_close(&fd[0]);
	}
	if (fd[1] > 2)
	{
		dup2(fd[1], STDOUT_FILENO);
		file_close(&fd[1]);
	}
}

void	pipex_close(t_parser *ps)
{
	t_list	*exec;
	t_exec	*ex;

	exec = ps->exec;
	while (exec)
	{
		ex = (t_exec *) exec->content;
		file_close(&ex->pipefd[0]);
		file_close(&ex->pipefd[1]);
		exec = exec->next;
	}
}

int			pipex_error(t_parser *ps, char *msg, t_error err, int errnum);
