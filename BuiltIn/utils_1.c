/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:46:32 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/08 12:29:27 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
