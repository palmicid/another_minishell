/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:26:22 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/08 15:39:01 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_splitdup(char **origin)
{
	char	**new;
	int		tmp;
	int		i;

	tmp = count_element_p2p(origin);
	new = (char **)malloc((tmp + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	new[tmp] = 0;
	i = 0;
	while (i < tmp)
	{
		new[i] = ft_strdup(origin[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
