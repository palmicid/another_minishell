/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudopipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:05:07 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/08 12:50:05 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	pipex_exec(t_exec *exec, t_parser *ps)
{
	int	ignore[2];
	int	status;

	ignore[0] = 0;
	ignore[1] = 1;
	status = fs_check(exec->infile, &ignore[0]);
	if (status != 0)
		return (status); //error
	print_debug(2, "infile is fd", ft_itoa(ignore[0]));
	status = fs_check(exec->outfile, &ignore[1]);
	if (status != 0)
		return (status); //error
	print_debug(2, "outfile is fd", ft_itoa(ignore[1]));
	print_debug(1, "Checking command...");
	status = cmd_findpath(exec->cmdarr, ps);
	if (status != 0)
		return (status); //error
	pipex_close(ps, ignore[0], ignore[1]);
	dup_close(ignore);
	execve(exec->cmdarr[0], exec->cmdarr, ps->envp);
	return (0);
}

void	pipex_close(t_parser *ps, int ig0, int ig1)
{
	t_list	*exec;
	t_exec	*ex;

	exec = ps->exec;
	while (exec)
	{
		ex = (t_exec *) exec->content;
		if (ex->pipefd[0] != ig0 && ex->pipefd[1] != ig0)
			file_close(&ex->pipefd[0]);
		if (ex->pipefd[0] != ig1 && ex->pipefd[1] != ig1)
			file_close(&ex->pipefd[1]);
		exec = exec->next;
	}
}

void	dup_close(int *fd)
{
	if (fd[0] > 2)
	{
		print_debug(3, "duping fd", ft_itoa(fd[0]), " to stdin");
		dup2(fd[0], STDIN_FILENO);
		file_close(&fd[0]);
	}
	if (fd[1] > 2)
	{
		print_debug(3, "duping fd", ft_itoa(fd[0]), " to stdout");
		dup2(fd[1], STDOUT_FILENO);
		file_close(&fd[1]);
	}
}

int			pipex_error(t_parser *ps, char *msg, t_error err, int errnum);
