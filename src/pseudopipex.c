/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudopipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:05:07 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/09 08:59:24 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	pipex_exec(t_exec *exec, t_parser *ps)
{
	int	ignore[2];
	int	status;

	ignore[0] = 0;
	ignore[1] = 1;
	status = fs_check(exec->infile, &ignore[0], ps);
	if (status != 0)
		return (status); //error
	print_debug(2, "infile is fd", ft_itoa(ignore[0]));
	status = fs_check(exec->outfile, &ignore[1], ps);
	if (status != 0)
		return (status); //error
	print_debug(2, "outfile is fd", ft_itoa(ignore[1]));
	print_debug(1, "Checking command...");
	status = cmd_findpath(exec->cmdarr, ps);
	if (status != 0)
		return (status); //error
	pipex_close(ps, ignore[0], ignore[1]);
	dup_close(ignore);
	status = execve_builtin(exec, ps);
	if (status >= 0)
		return (status);
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

void	execve_builtin(t_exec *exec, t_parser *ps)
{
	int	status;

	status = INT_MIN;
	if (ft_strncmp(exec->cmdarr[0], "exit", 5) == 0)
		status = mini_exit(exec->cmdarr);
	if (ft_strncmp(exec->cmdarr[0], "echo", 5) == 0)
		status = mini_echo(exec->cmdarr);
	if (ft_strncmp(exec->cmdarr[0], "cd", 3) == 0)
		status = mini_cd(exec->cmdarr);
	if (ft_strncmp(exec->cmdarr[0], "pwd", 4) == 0)
		status = mini_pwd(exec->cmdarr);
	if (ft_strncmp(exec->cmdarr[0], "export", 7) == 0)
		status = mini_export(exec->cmdarr);
	if (ft_strncmp(exec->cmdarr[0], "unset", 6) == 0)
		status = mini_unset(exec->cmdarr);
	if (ft_strncmp(exec->cmdarr[0], "env", 4) == 0)
		status = mini_env(exec->cmdarr);
	if (status > 0)
	{
		ps = ps_free(ps);
		return (status);
	}
}
