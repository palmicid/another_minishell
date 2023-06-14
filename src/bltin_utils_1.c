/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:46:32 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/14 15:54:22 by pruangde         ###   ########.fr       */
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

char	*getvarname(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != '='))
		i++;
	return (ft_strndup(str, i));
}

char	**sp_splitndup(char **dst, char **src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			ft_free_p2p_char(dst);
			return (NULL);
		}
		i++;
	}
	return (dst);
}

int	cx_validvar(char *name)
{
	int	i;

	i = 1;
	if (ft_isalpha(name[0]) || (name[0] == '_'))
	{
		while (name[i] && (ft_isalnum(name[i]) || name[i] == '_'))
			i++;
		if (name[i] == 0)
			return (0);
		return (1);
	}
	else
		return (1);
	return (1);
}

int	free_reterr_export(char **ptr)
{
	if (cx_validvar(ptr[0]))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(ptr[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("not a valid identifier", 2);
	}
	free(ptr[0]);
	ptr = NULL;
	return (1);
}
