/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:20:44 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/08 15:42:59 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"

static char	**err_tmp_free(char **tofree)
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
			return (err_tmp_free(tmp));
		i++;
		it++;
	}
	return (tmp);
}

void	mini_unset(char *todel)
{
	int		i;
	int		pos;
	int		count;
	char	**tmp;

	if ((todel == NULL) || (getenv(todel) == NULL))
		return ;
	pos = find_pos_env(todel);
	count = count_element_p2p(environ);
	tmp = (char **)malloc(count * sizeof(char *));
	i = 0;
	tmp = envdup(i, i, tmp, pos);
	if (!tmp)
		return ;
	i = pos + 1;
	tmp = envdup(i, i - 1, tmp, count);
	if (!tmp)
		return ;
	environ = err_tmp_free(environ);
	environ = tmp;
	tmp = NULL;
	return ;
}
