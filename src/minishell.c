/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 09:53:41 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	soloexecve(t_listcmd *cmdlist, t_data *data)
{
	if (cmdlist->next == NULL)
	{
		if (ft_strncmp(cmdlist->cmd[0], "exit", 5) == 0)
			data->exit_stat = mini_exit(cmdlist->cmd) % 255;
		else if (ft_strncmp(cmdlist->cmd[0], "export", 7) == 0)
			data->exit_stat = mini_export(cmdlist->cmd) % 255;
		else if (ft_strncmp(cmdlist->cmd[0], "unset", 6) == 0)
			data->exit_stat = mini_unset(cmdlist->cmd) % 255;
		else if (ft_strncmp(cmdlist->cmd[0], "cd", 3) == 0)
			data->exit_stat = mini_cd(cmdlist->cmd) % 255;
		else
			data->exit_stat = executor(cmdlist, environ) % 255;
	}
	else
		data->exit_stat = executor(cmdlist, environ) % 255;
	if (cmdlist->next == NULL && ft_strncmp(cmdlist->cmd[0], "exit", 5) == 0)
	{
		//ft_putendl_fd(cmdlist->cmd[0], 1);
		return (1);
	}
	return (0);
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

static void	exit_end(t_data *data, char **strcmd)
{
	int	n;

	n = data->exit_stat;
	free(strcmd[0]);
	end_environ(data);
	exit(n);
}

// the child going to be parent for all program
int	process(char *strcmd, t_data *data)
{
	int			stat;
	t_listcmd	*cmdlist;

	cmdlist = NULL;
	add_history(strcmd);
	cmdlist = str_split(strcmd, data);
	print_debug(1, cmdlist);
	stat = soloexecve(cmdlist, data);
	cmdlist = free_cmdlist(cmdlist);
	return (stat);
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
		strcmd = readline("minishell-1.0 beta$ ");
		if (!strcmd)
			break ;
		else if (strcmd[0] == '\0')
			;
		else if (ft_strlen(strcmd) > 0)
			x = process(strcmd, &data);
		if (x == 1)
			exit_end(&data, &strcmd);
		free(strcmd);
	}
	ft_putendl_fd("exit", 1);
	exit(end_environ(&data));
}
