/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_errmsg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:01:54 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 10:45:03 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"

void	bltin_err_msg(char *str)
{
	char	*strerr;

	strerr = strerror(errno);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("minshell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerr, 2);
}

void	bltin_exiterr_msg(char *str)
{
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("numeric argument required", 2);
}
