/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 11:54:01 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	soloexit(char *strcmd, t_data *data)
{
	int status;

	status = mini_exit(&strcmd);
	free(strcmd);
	end_environ(data);
	exit(status);
}

int	ismulticmd(char *strcmd)
{
	int	i;

	i = 0;
	while (strcmd[i])
	{
		if (strcmd[i] == '|')
			return (0);
		if (strcmd[i] == 34 || strcmd[i] == 39)
			i = find_pair(strcmd, i);
		i++;
	}
}

// the child going to be parent for all program
void	process(char *strcmd, t_data *data)
{
	// int		stat;
	t_listcmd	*cmdlist;

	cmdlist = NULL;
	add_history(strcmd);
	cmdlist = str_split(strcmd, data);
	// to execute
	test_print(cmdlist);
	data->exit_stat = executor(cmdlist, data->env) % 255;
	// data->exit_stat = to_execute(cmdlist);
	cmdlist = free_cmdlist(cmdlist);
}

int	main(void)
{
	char	*strcmd;
	t_data	data;

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
		else if (ft_strncmp(strcmd, "exit", 5) == 0
		&& ismulticmd(strcmd) == NULL)
			soloexit(strcmd, &data);
		else if (ft_strlen(strcmd) > 0)
			process(strcmd, &data);
		free(strcmd);
	}
	ft_putendl_fd("exit", 1);
	exit(end_environ(&data));
}

