/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:36:36 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/08 12:40:52 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

t_fileset	*fs_init(char *name, int fd, t_filetype type)
{
	t_fileset	*fs;

	fs = malloc(sizeof(t_fileset));
	if (!fs)
		return (NULL);
	fs->fd = fd;
	fs->type = type;
	fs->name = ft_strdup(name);
	if (fs->name == NULL && fs->name != NULL)
	{
		fs_free(fs);
		return (NULL);
	}
	return (fs);
}

void	*fs_free(void *ptr)
{
	t_fileset	*fs;

	fs = (t_fileset *) ptr;
	if (fs == NULL)
		return (NULL);
	if (fs->fd > 2)
		file_close(&fs->fd);
	if (fs->name != NULL)
		free(fs->name);
	free(fs);
	return (NULL);
}

void	fs_free2(void *ptr)
{
	t_fileset	*fs;

	fs = (t_fileset *) ptr;
	if (fs == NULL)
		return ;
	if (fs->fd > 2)
		file_close(&fs->fd);
	if (fs->name != NULL)
		free(fs->name);
	free(fs);
}

int	fs_check(t_list *fslst, int *fd)
{
	t_fileset	*fs;
	t_list		*ptr;
	int			status;

	status = 0;
	ptr = fslst;
	while (ptr)
	{
		fs = (t_fileset *) ptr->content;
		if (fs->type == INFILE || fs->type == OUTFILE || fs->type == APPEND)
			status = file_open(fs);
		else if (fs->type == HEREDOC)
			status = heredoc_open(fs);
		if (status != 0)
			return (status); // error
		*fd = fs->fd;
		print_debug(6, "opening: ", fs->name, ", type: ", ft_itoa(fs->type), " at fd", ft_itoa(fs->fd));
		if (ptr->next != NULL && fs->fd > 2)
			file_close(&fs->fd);
		ptr = ptr->next;
	}
	return (status);
}
