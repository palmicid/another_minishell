/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:27:46 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/08 08:39:06 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

t_exec	*exec_init(void)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->pid = INT_MIN;
	exec->cmdlst = NULL;
	exec->cmdarr = NULL;
	exec->infile = NULL;
	exec->outfile = NULL;
	exec->pipefd[0] = INT_MIN;
	exec->pipefd[1] = INT_MIN;
	if (pipe(exec->pipefd) == -1)
		return (exec_free(exec));
	return (exec);
}

void	*exec_free(void *exec)
{
	t_exec	*ex;

	ex = (t_exec *) exec;
	if (ex == NULL)
		return (NULL);
	if (ex->pipefd[0] > 2)
		file_close(&ex->pipefd[0]);
	if (ex->pipefd[1] > 2)
		file_close(&ex->pipefd[1]);
	ft_arrclear(ex->cmdarr);
	ft_lstclear(&ex->cmdlst, free);
	ft_lstclear(&ex->infile, fs_free2);
	ft_lstclear(&ex->outfile, fs_free2);
	free(ex);
	return (NULL);
}

void	exec_free2(void *exec)
{
	t_exec	*ex;

	ex = (t_exec *)exec;
	if (ex == NULL)
		return ;
	if (ex->pipefd[0] > 2)
		file_close(&ex->pipefd[0]);
	if (ex->pipefd[1] > 2)
		file_close(&ex->pipefd[1]);
	ft_arrclear(ex->cmdarr);
	ft_lstclear(&ex->cmdlst, free);
	ft_lstclear(&ex->infile, fs_free2);
	ft_lstclear(&ex->outfile, fs_free2);
	free(ex);
	return ;
}
