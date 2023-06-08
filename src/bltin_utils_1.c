/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:46:32 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/08 14:12:08 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"

int	find_pos_env(char *tofind)
{
	int		pos;
	int		len;
	char	*tf;

	pos = 0;
	tf = ft_strjoin(tofind, "=");
	if (!tf)
		return (-1);
	len = ft_strlen(tf);
	while (environ[pos])
	{
		if (ft_strncmp(environ[pos], tf, len) == 0)
		{
			free(tf);
			return (pos);
		}
		pos++;
	}
	free(tf);
	return (-1);
}
