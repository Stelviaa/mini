/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 03:39:38 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 06:50:04 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_en_here_doc(t_cmd *cmd, t_file *file, int coor[2])
{
	file->type = 3;
	coor[1]++;
	if (ft_strlen(cmd->arg[coor[0]]) > 2)
		file->fd_file = ft_split(cmd->arg[coor[0]], '<')[0];
	else
		file->fd_file = ft_strdup(cmd->arg[coor[0] + 1]);
	file->fd_file = reset_quote(file->fd_file);
}

void	parsing_en(t_cmd *cmd, t_file *file, int coor[2])
{
	file->type = 1;
	if (ft_strlen(cmd->arg[coor[0]]) > 1)
		file->fd_file = ft_split(cmd->arg[coor[0]], '<')[0];
	else
		file->fd_file = ft_strdup(cmd->arg[coor[0] + 1]);
	file->fd_file = reset_quote(file->fd_file);
}

void	parsing_ex_append(t_cmd *cmd, t_file *file, int coor[2])
{
	file->type = 4;
	coor[1]++;
	if (ft_strlen(cmd->arg[coor[0]]) > 2)
		file->fd_file = ft_split(cmd->arg[coor[0]], '>')[0];
	else
		file->fd_file = ft_strdup(cmd->arg[coor[0] + 1]);
	file->fd_file = reset_quote(file->fd_file);
}

void	parsing_ex(t_cmd *cmd, t_file *file, int coor[2])
{
	file->type = 2;
	if (ft_strlen(cmd->arg[coor[0]]) > 1)
		file->fd_file = ft_split(cmd->arg[coor[0]], '>')[0];
	else
		file->fd_file = ft_strdup(cmd->arg[coor[0] + 1]);
	file->fd_file = reset_quote(file->fd_file);
}

void	choose_parsing(t_cmd *cmd, t_file *file, char *line, int *coor)
{
	while (cmd->arg[coor[0]])
	{
		coor[1] = 0;
		while (cmd->arg[coor[0]][coor[1]])
		{
			if (cmd->arg[coor[0]][coor[1]] == '<' 
				&& cmd->arg[coor[0]][coor[1] + 1]
					&& cmd->arg[coor[0]][coor[1] + 1] == '<' )
				parsing_en_here_doc(cmd, file, coor);
			else if (cmd->arg[coor[0]][coor[1]] == '<')
				parsing_en(cmd, file, coor);
			if (cmd->arg[coor[0]][coor[1]] == '>' 
				&& cmd->arg[coor[0]][coor[1] + 1]
					&& cmd->arg[coor[0]][coor[1] + 1] == '>' )
				parsing_ex_append(cmd, file, coor);
			else if (cmd->arg[coor[0]][coor[1]] == '>')
				parsing_ex(cmd, file, coor);
			coor[1]++;
		}
		if (file->type != 0)
			file->next = init_tfile(line);
		if (file->type != 0)
			file = file->next; 
		coor[0]++;
	}
}
