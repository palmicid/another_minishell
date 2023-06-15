/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 11:52:46 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 09:57:53 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_handler(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_int_handler_noredis(int sig)
{
	(void)sig;
	if (sig == SIGINT)
		ft_putendl_fd("", STDOUT_FILENO);
}

void	signal_int_handling(int mode)
{
	struct sigaction	sig_int;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	if (mode == 1)
		sig_int.sa_handler = sig_int_handler;
	else if (mode == 2)
		sig_int.sa_handler = sig_int_handler_noredis;
	sigaction(SIGINT, &sig_int, NULL);
}

// ctrl+C and ctrl+backspace
void	signal_handling(void)
{
	struct sigaction	sig_quit;

	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = 0;
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_quit, NULL);
	signal_int_handling(1);
}
