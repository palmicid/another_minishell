/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:50:14 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/15 09:23:54 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	file_open(t_fileset *fs, t_parser *ps)
{
	if (access(fs->name, F_OK) != 0)
	{
		if (fs->type == INFILE)
			executor_error(ps, fs->name, FILE_ERROR, errno); //1
		else if (fs->type == OUTFILE || fs->type == APPEND)
			fs->fd = open(fs->name, O_CREAT | O_WRONLY, 0644);
		file_close(&fs->fd);
	}
	if (fs->type == INFILE)
	{
		if (access(fs->name, R_OK) != 0)
			executor_error(ps, fs->name, ACCESS_ERROR, errno); //1
		fs->fd = open(fs->name, O_RDONLY);
			print_debug(4, "opened ", fs->name, " (read) at fd ", ft_itoa(fs->fd));
	}
	else if (fs->type == OUTFILE || fs->type == APPEND)
	{
		if (access(fs->name, W_OK) != 0)
			executor_error(ps, fs->name, ACCESS_ERROR, errno); //1
		if (fs->type == APPEND)
		{
			fs->fd = open(fs->name, O_WRONLY | O_APPEND);
			print_debug(4, "opened ", fs->name, " (append) at fd ", ft_itoa(fs->fd));
		}
		else if (fs->type == OUTFILE)
		{
			fs->fd = open(fs->name, O_WRONLY | O_TRUNC);
			print_debug(4, "opened ", fs->name, " (trunc) at fd ", ft_itoa(fs->fd));
		}
	}
	return (0);
}

int	heredoc_open(t_fileset *fs, t_parser *ps)
{
	char	*line;
	char	*name;

	name = malloc(ft_strlen(fs->name) + 2);
	if (name == NULL)
		executor_error(ps, NULL, ALLOC_ERROR, errno);
	ft_strlcpy(name, fs->name, ft_strlen(fs->name) + 1);
	ft_strlcat(name, "\n", ft_strlen(fs->name) + 2);
	fs->fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(line, name, strlen(name) + 1) == 0)
			break ;
		write(fs->fd, line, strlen(line));
		if (line != NULL)
			free(line);
	}
	if (line != NULL)
		free(line);
	file_close(&fs->fd);
	fs->fd = open("/tmp/heredoc", O_RDONLY);
	ft_free(name);
	return (0);
}

void	file_close(int *fd)
{
	if (*fd > 2)
		close(*fd);
	*fd = INT_MIN;
}
