/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:27:40 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/07 18:34:34 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_strcut	*inside_cxmetavalid(t_strcut **head, char *str)
{
	err_redirpipe(str);
	return (free_strcutlist(head));
}

t_strcut	*createnew_strcut(void)
{
	t_strcut	*listnew;

	listnew = (t_strcut *)malloc(sizeof(t_strcut));
	if (!listnew)
		return (NULL);
	listnew->stat = 0;
	listnew->str = NULL;
	listnew->next = NULL;
	return (listnew);
}

t_listcmd	*createnew_lstcmd(void)
{
	t_listcmd	*listnew;

	listnew = (t_listcmd *)malloc(sizeof(t_listcmd));
	if (!listnew)
		return (NULL);
	listnew->next = NULL;
	return (listnew);
}

t_c	*create_countptr(void)
{
	t_c	*new;

	new = (t_c *)malloc(sizeof(t_c));
	if (!new)
		return (NULL);
	new->i = 0;
	new->j = 0;
	new->st = 0;
	return (new);
}
