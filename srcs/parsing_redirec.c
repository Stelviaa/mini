/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 08:15:45 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/29 01:27:30 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_name(char	**str, int mode)
{
	int		i;
	int		j;
	int		quote;

	i = -1;
	j = -1;
	quote = 0;
	while (str[++i])
	{
		while (str[i][++j])
		{
			if ((str[i][j] == 39 || str[i][j] == 34) && !quote)
				quote = str[i][j];
			else if (str[i][j] == quote)
				quote = 0;
			if (!quote && str[i][j] == '<' && mode == 1)
				return (i + 1);
			if (!quote && str[i][j] == '>' && mode == 2)
				return (i + 1);
		}
		j = -1;
	}
	return (-1);
}


t_file	*init_tfile(char *line)
{
	t_file	*file;

	(void)line;
	file = malloc(sizeof(t_file));
	file->fd_file = 0;
	file->type = 0;
	file->next = 0;
	return (file);
}


void	manage_redirec(char **envp, t_cmd *cmd, char *line)
{
	int		x;
	int		y;
	t_file	*file;

	(void)envp;
	(void)line;
	x = 0;
	y = 0;
	cmd->file = init_tfile(line);
	file = cmd->file;
	while (cmd->arg[x])
	{
		y = 0;
		while (cmd->arg[x][y])
		{
			if (cmd->arg[x][y] == '<' && cmd->arg[x][y + 1] && cmd->arg[x][y + 1] == '<' )
			{
				if (file->type != 0)
				{
					file->next = init_tfile(line);
					file = file->next; 
				}
				file->type = 3;
				y ++;
				if (ft_strlen(cmd->arg[x]) > 2)
					file->fd_file = ft_split(cmd->arg[x], '<')[0];
				else
					file->fd_file = ft_strdup(cmd->arg[x + 1]);
			}
			else if (cmd->arg[x][y] == '<')
			{
				if (file->type != 0)
				{
					file->next = init_tfile(line);
					file = file->next; 
				}
				file->type = 1;
				if (ft_strlen(cmd->arg[x]) > 2)
					file->fd_file = ft_split(cmd->arg[x], '<')[0];
				else
					file->fd_file = ft_strdup(cmd->arg[x + 1]);
			}
			if (cmd->arg[x][y] == '>' && cmd->arg[x][y + 1] && cmd->arg[x][y + 1] == '>' )
			{
				if (file->type != 0)
				{
					file->next = init_tfile(line);
					file = file->next; 
				}
				file->type = 4;
				y ++;
				if (ft_strlen(cmd->arg[x]) > 1)
					file->fd_file = ft_split(cmd->arg[x], '>')[0];
				else
					file->fd_file = ft_strdup(cmd->arg[x + 1]);
			}
			else if (cmd->arg[x][y] == '>')
			{
				if (file->type != 0)
				{
					file->next = init_tfile(line);
					file = file->next; 
				}
				file->type = 2;
				if (ft_strlen(cmd->arg[x]) > 1)
					file->fd_file = ft_split(cmd->arg[x], '>')[0];
				else
					file->fd_file = ft_strdup(cmd->arg[x + 1]);
			}
			y ++;
		}
		x ++;
	}
}
