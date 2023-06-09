/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 11:32:28 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		&& ft_strchr(strcmd, '|') == NULL)
			soloexit(strcmd, &data);
		else if (ft_strlen(strcmd) > 0)
			process(strcmd, &data);
		free(strcmd);
	}
	ft_putendl_fd("exit", 1);
	exit(end_environ(&data));
}

void	soloexit(char *strcmd, t_data *data)
{
	int status;

	status = mini_exit(&strcmd);
	free(strcmd);
	end_environ(data);
	exit(status);
}
