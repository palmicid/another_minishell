/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:03:36 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/15 09:55:45 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

t_parser	*ps_init(char **envp)
{
	t_parser	*ps;

	ps = malloc(sizeof(t_parser));
	if (!ps)
		return (NULL);
	ps->exec = NULL;
	ps->envp = envp;
	ps->path = ps_getpath(envp);
	if (!ps->path)
		return (ps_free(ps));
	ps->status = 0;
	return (ps);
}

char	**ps_getpath(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	path = malloc(sizeof(char *) * 2);
	if (!path)
		return (NULL);
	path[0] = ft_strdup("");
	path[1] = NULL;
	return (path);
}

void	*ps_free(void *ps)
{
	t_parser	*pss;

	pss = (t_parser *) ps;
	if (!pss)
		return (NULL);
	if (pss->exec)
		ft_lstclear(&pss->exec, exec_free2);
	ft_arrclear(pss->path);
	free(pss);
	return (NULL);
}

void	ps_free2(void *ps)
{
	t_parser	*pss;

	pss = (t_parser *) ps;
	if (!pss)
		return ;
	if (pss->exec)
		ft_lstclear(&pss->exec, exec_free2);
	ft_arrclear(pss->path);
	free(pss);
}
