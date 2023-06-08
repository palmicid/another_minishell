/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 08:12:30 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/08 08:41:55 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"
#include <stdarg.h>

void	print_debug(int argc, ...)
{
	va_list	va;
	char	*str;

	va_start(va, argc);
	if (DEBUG == 1)
	{
		while (argc--)
		{
			str = va_arg(va, char *);
			ft_putstr_fd(str, 1);
		}
		ft_putendl_fd("", 1);
	}
	va_end(va);
}
