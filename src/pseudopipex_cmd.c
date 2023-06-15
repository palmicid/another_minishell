/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudopipex_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:18:11 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/15 09:57:14 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	cmd_findpath(char **cmd, t_parser *ps)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (0);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (0);
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (0);
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (0);
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (0);
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (0);
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (0);
	if (ft_strchr(cmd[0], '/') == NULL)
		return (cmdcheck_path(cmd, ps));
	else
		return (cmdcheck_notpath(cmd, ps));
}

int	cmdcheck_path(char **cmd, t_parser *ps)
{
	int		i;
	char	*newpath;

	i = -1;
	newpath = NULL;
	if (ps->path == NULL)
		executor_error(ps, cmd[0], CMD_ERROR, 127);
	while (ps->path[++i] != NULL)
	{
		newpath = ft_strprepend(cmd[0], ps->path[i]);
		if (access(newpath, F_OK) == 0)
		{
			if (access(newpath, X_OK) != 0)
				executor_error(ps, cmd[0], ACCESS_ERROR, 126);
			cmd[0] = ft_free(cmd[0]);
			cmd[0] = newpath;
			return (0);
		}
		newpath = ft_free(newpath);
	}
	executor_error(ps, cmd[0], CMD_ERROR, 127);
	return (127);
}

char	*ft_strprepend(char *s1, char *s2)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (s1[0] == '\0')
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s2, ft_strlen(s2) + 1);
	ft_strlcat(str, "/", ft_strlen(s2) + 2);
	ft_strlcat(str, s1, ft_strlen(s1) + ft_strlen(s2) + 2);
	return (str);
}

int	cmdcheck_notpath(char **cmd, t_parser *ps)
{
	(void) ps;
	if (access(cmd[0], F_OK) == 0)
	{
		if (access(cmd[0], X_OK) != 0)
		{
			executor_error(ps, cmd[0], ACCESS_ERROR, 126);
		}
		else
			return (0);
	}
	else
	{
		executor_error(ps, cmd[0], FILE_ERROR, 127);
	}
}
