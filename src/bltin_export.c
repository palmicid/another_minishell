/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:20:25 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 10:56:47 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"

static int	sp_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	if (s1[i] == '=')
		return (-1);
	else if (s2[i] == '=')
		return (1);
	return (s1[i] - s2[i]);
}

// if ret == minus --> swap
// export notprint the last _
static char	**to_sort(char **ts, int count)
{
	int		i;
	char	*tmp;

	i = 0;
	while (count > 1)
	{
		i = 0;
		while (i < count)
		{
			if (sp_strcmp(ts[i], ts[i + 1]) > 0)
			{
				tmp = ts[i];
				ts[i] = ts[i + 1];
				ts[i + 1] = tmp;
			}
			i++;
		}
		count--;
	}
	return (ts);
}

static int	print_sortenv(void)
{
	char	**sort;
	int		i;
	int		count;

	sort = ft_splitdup(environ);
	if (!sort)
		return (1);
	count = count_element_p2p(sort) - 2;
	sort = to_sort(sort, count);
	i = 0;
	while (sort[i] && i < count + 1)
	{
		printf("%s\n", sort[i]);
		i++;
	}
	return (0);
}

int	add_newvar(char	*strvar)
{
	int		count;
	char	**tmp;

	count = count_element_p2p(environ) + 1;
	tmp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		return (1);
	tmp = sp_splitndup(tmp, environ, count - 2);
	tmp[count - 2] = ft_strdup(strvar);
	tmp[count - 1] = ft_strdup(environ[count - 2]);
	tmp[count] = NULL;
	ft_free_p2p_char(environ);
	environ = tmp;
	tmp = NULL;
	return (0);
}

// cx arg[1] find '=' if no stop
// get name if isalnum(name) not ok --> not a valid identifier
int	mini_export(char **strarr)
{
	char	*name;
	int		pos;

	if (strarr[1] == NULL)
		return (print_sortenv());
	if (find_charpos(strarr[1], '=') == -1)
		return (0);
	name = getvarname(strarr[1]);
	if (getenv(name))
	{
		pos = find_pos_env(name);
		free(environ[pos]);
		environ[pos] = ft_strdup(strarr[1]);
	}
	else
	{
		if (cx_validvar(name))
			return (free_reterr_export(&name));
		if (add_newvar(strarr[1]))
			return (free_reterr_export(&name));
	}
	free(name);
	return (0);
}
