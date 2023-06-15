/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:52:18 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/15 13:34:34 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	executor_free(t_parser *ps)
{
	int	status;

	status = ps->status;
	ps_free(ps);
	return (WEXITSTATUS(status));
}

int	executor_error(t_parser *ps, char *msg, t_error err, int errnum)
{
	ft_putstr_fd("minishell: ", 2);
	if (err == CMD_ERROR || err == FILE_ERROR || err == ACCESS_ERROR)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (err == CMD_ERROR)
		ft_putendl_fd("command not found", 2);
	else if (err == ACCESS_ERROR)
		ft_putendl_fd("Permission denied", 2);
	else if (err == FILE_ERROR)
		ft_putendl_fd("No such file or directory", 2);
	else
		ft_putendl_fd(strerror(errnum), 2);
	ps_free(ps);
	if (errnum > 0 && errnum < 126)
		errnum = 1;
	exit(errnum);
}
