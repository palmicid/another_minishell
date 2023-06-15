/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 04:15:44 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 17:28:20 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if i++ == nothing malloc 

static char	*getvarname_qm(char *str, t_c *c)
{
	char	*name;
	int		st;

	(c->i)++;
	if (str[c->i] == '?')
	{
		name = ft_calloc(2, sizeof(char));
		name[0] = '?';
		(c->i)++;
	}
	else if (ft_isalpha(str[c->i]) == 0 && str[c->i] != '_')
	{
		name = ft_calloc(1, sizeof(char));
		(c->i)++;
	}
	else
	{
		st = c->i;
		while (str[c->i] && (ft_isalnum(str[c->i]) == 1 || str[c->i] == '_'))
			(c->i)++;
		name = ft_strndup(str + st, (c->i - st));
	}
	return (name);
}

static char	*sub_expand_proc(char *str, t_c *c, char *fin)
{
	char	*name;
	char	*var;
	char	*varfree;

	varfree = NULL;
	name = getvarname_qm(str, c);
	if (!name)
		return (NULL);
	var = my_getenv(name);
	if (!var)
	{
		if (ft_strncmp(name, "?", 2) == 0)
			varfree = ft_itoa(g_data.exit_stat);
		else
			varfree = ft_calloc(1, sizeof(char));
		fin = ssp_strjoin(fin, varfree, 1, 0);
	}
	else
		fin = ssp_strjoin(fin, var, 1, 0);
	free(name);
	return (fin);
}

static char	*subinsub_expand(char *fin, t_c *c, t_strcut *cur)
{
	if (c->st != c->i)
		fin = ssp_strnjoin(fin, cur->str + c->st, (c->i - c->st), 0);
	if (!fin)
		return (fin);
	fin = sub_expand_proc(cur->str, c, fin);
	if (!fin)
		return (fin);
	c->st = (c->i)--;
	return (fin);
}

// pass 0 to both int 
static void	sub_expand(t_strcut *cur)
{
	char	*fin;
	t_c		*c;

	c = create_countptr();
	if (!c)
		return (set_error(cur));
	fin = ft_calloc(1, sizeof(char));
	if (!fin)
		return (set_error(cur));
	while (cur->str[c->i])
	{
		if (cur->str[c->i] == '$')
		{
			fin = subinsub_expand(fin, c, cur);
			if (!fin)
				return (set_error(cur));
		}
		c->i++;
	}
	if (c->st != c->i)
		fin = ssp_strjoin(fin, cur->str + c->st, 1, 0);
	free(cur->str);
	cur->str = fin;
}

void	expand_var(t_strcut *head)
{
	t_strcut	*cur;

	cur = head;
	while (cur)
	{
		if (cur->stat == 0 || cur->stat == 2)
		{
			sub_expand(cur);
			if (cur->stat == -1)
				return (set_error(head));
		}
		cur = cur->next;
	}
}
