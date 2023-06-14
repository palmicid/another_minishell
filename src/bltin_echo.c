/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:19:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/14 17:29:54 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"

static void	print_echo(char **strarr, int st)
{
	int	count;
	
	count = count_element_p2p(strarr);
	if (strarr[st])
		ft_putstr_fd(strarr[st], 1);
	st++;
	while (st < count)
	{
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(strarr[st], 1);
		st++;
	}
}

int	mini_echo(char **strarr)
{
	if (strarr[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (strarr[1][0] == '-')
	{
		if (ft_strncmp(strarr[1], "-n", 3) == 0)
		{
			if (strarr[2] == NULL)
				return (0);
			print_echo(strarr, 2);
			return (0);
		}
	}
	print_echo(strarr, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
