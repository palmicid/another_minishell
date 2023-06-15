/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_errmsg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:01:54 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 16:37:28 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bltin_err_msg(char *str)
{
	char	*strerr;

	strerr = strerror(errno);
	ft_putstr_fd("minshell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerr, 2);
}

void	bltin_exiterr_msg(char *str)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("numeric argument required", 2);
}

int	cx_signfirstpos(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}
