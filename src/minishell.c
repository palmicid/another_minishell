/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 12:07:05 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	soloexit(t_listcmd *cmdlist, t_data *data)
{
	data->exit_stat = mini_exit(cmdlist->cmd);
	ft_putendl_fd("exit", 1);
}

int	ismulticmd(char *strcmd)
{
	int	i;

	i = 0;
	while (strcmd[i])
	{
		if (strcmd[i] == '|')
			return (1);
		if (strcmd[i] == 34 || strcmd[i] == 39)
			i = find_pair(strcmd, i);
		i++;
	}
	return (0);
}

// the child going to be parent for all program
int	process(char *strcmd, t_data *data)
{
	// int		stat;
	t_listcmd	*cmdlist;

	cmdlist = NULL;
	add_history(strcmd);
	cmdlist = str_split(strcmd, data);
	// to execute
	test_print(cmdlist);
	if (cmdlist->next != NULL && ft_strchr(cmdlist->next->cmd, '|') != NULL)
	{
		soloexit(cmdlist, data);
		return (1);
	}
	else
		data->exit_stat = executor(cmdlist, data->env) % 255;
	// data->exit_stat = to_execute(cmdlist);
	cmdlist = free_cmdlist(cmdlist);
	return (0);
}

int	main(void)
{
	char	*strcmd;
	t_data	data;
	int		x;

	if (DEBUG == 1)
		ft_putendl_fd("DEBUG mode ON", 1);
	strcmd = NULL;
	init_environ(&data);
	signal_handling();
	while (1)
	{
		strcmd = readline("minishell-0.9a$ ");
		if (!strcmd)
			break ;
		else if (strcmd[0] == '\0')
			;
		else if (ft_strlen(strcmd) > 0)
			x = process(strcmd, &data);
		if (x == 1)
			exit_end(&data, strcmd);
		free(strcmd);
	}
	ft_putendl_fd("exit", 1);
	exit(end_environ(&data));
}

