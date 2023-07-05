/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:16:02 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 10:20:14 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_files_enter(t_file *file)
{
	int	fd;

	fd = 0;
	if (file->type == 1)
	{
		fd = open (file->fd_file, O_RDONLY);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			exit (0);
		}
	}
	if (file->type == 3)
	{
		fd = create_infile(file->fd_file);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			exit (0);
		}
	}
	return (fd);
}

int	open_files_exit(t_file *file)
{
	int	fd;

	fd = 0;
	if (file->type == 2)
	{
		fd = open (file->fd_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			exit(0);
		}
	}
	if (file->type == 4)
	{
		fd = open (file->fd_file, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			exit(0);
		}
	}
	return (fd);
}

void	redirection(t_cmd *cmd, t_file *file)
{
	int	i;
	int	fd[2];

	i = 0;
	fd[0] = 0;
	fd[1] = 0;
	while (file)
	{
		if (file->fd_file && (file->type == 1 || file->type == 3))
			fd[0] = open_files_enter(file);
		if (file->fd_file && (file->type == 2 || file->type == 4))
			fd[1] = open_files_exit(file);
		if (file->next
			&& (file->next->type == 1 || file->next->type == 3) && fd[0])
			close(fd[0]);
		if (file->next
			&& (file->next->type == 2 || file->next->type == 4) && fd[1])
			close(fd[1]);
		file = file->next;
	}
	cmd->in = dup(fd[0]);
	cmd->out = dup(fd[1]);
}
