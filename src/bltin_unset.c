/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:20:44 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/14 14:16:53 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"

static char	**tmp_free(char **tofree)
{
	ft_free_p2p_char(tofree);
	tofree[0] = NULL;
	return (tofree);
}

char	**envdup(int i, int it, char **tmp, int lim)
{
	while (environ[i] && (i < lim))
	{
		tmp[it] = ft_strdup(environ[i]);
		if (tmp[it] == NULL)
			return (tmp_free(tmp));
		i++;
		it++;
	}
	tmp[lim - 1] = NULL;
	return (tmp);
}

int	micro_unset(char *todel)
{
	int		i;
	int		pos;
	int		count;
	char	**tmp;

	if ((todel == NULL) || (getenv(todel) == NULL))
		return (1);
	pos = find_pos_env(todel);
	count = count_element_p2p(environ);
	tmp = (char **)malloc(count * sizeof(char *));
	if (!tmp)
		return (1);
	i = 0;
	tmp = envdup(i, i, tmp, pos + 1);
	if (!tmp)
		return (1);
	i = pos + 1;
	tmp = envdup(i, pos, tmp, count);
	if (!tmp)
		return (1);
	// environ = tmp_free(environ);
	environ = tmp;
	tmp = NULL;
	return (0);
}

int	mini_unset(char **strarr)
{
	int	i;
	int status;

	status = 0;
	if (strarr[1] == NULL)
		return (0);
	i = 1;
	while (strarr[i])
	{
		status = micro_unset(strarr[i]);
		i++;
	}
	return (status);
}
