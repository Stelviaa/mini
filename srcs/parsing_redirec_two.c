/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 03:39:38 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 03:59:31 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_en_here_doc(t_cmd *cmd, t_file *file, int coor[2], char *line)
{
	if (file->type != 0)
	{
		file->next = init_tfile(line);
		file = file->next; 
	}
	file->type = 3;
	coor[1]++;
	if (ft_strlen(cmd->arg[coor[0]]) > 2)
		file->fd_file = ft_split(cmd->arg[coor[0]], '<')[0];
	else
		file->fd_file = ft_strdup(cmd->arg[coor[0] + 1]);
	file->fd_file = reset_quote(file->fd_file);
}

void	parsing_en(t_cmd *cmd, t_file *file, int coor[2], char *line)
{
	if (file->type != 0)
	{
		file->next = init_tfile(line);
		file = file->next; 
	}
	file->type = 1;
	if (ft_strlen(cmd->arg[coor[0]]) > 1)
		file->fd_file = ft_split(cmd->arg[coor[0]], '<')[0];
	else
		file->fd_file = ft_strdup(cmd->arg[coor[0] + 1]);
	file->fd_file = reset_quote(file->fd_file);
}

void	parsing_ex_append(t_cmd *cmd, t_file *file, int coor[2], char *line)
{
	if (file->type != 0)
	{
		file->next = init_tfile(line);
		file = file->next; 
	}
	file->type = 4;
	coor[1]++;
	if (ft_strlen(cmd->arg[coor[0]]) > 2)
		file->fd_file = ft_split(cmd->arg[coor[0]], '>')[0];
	else
		file->fd_file = ft_strdup(cmd->arg[coor[0] + 1]);
	file->fd_file = reset_quote(file->fd_file);
}

void	parsing_ex(t_cmd *cmd, t_file *file, int coor[2], char *line)
{
	if (file->type != 0)
	{
		file->next = init_tfile(line);
		file = file->next; 
	}
	file->type = 2;
	if (ft_strlen(cmd->arg[coor[0]]) > 1)
		file->fd_file = ft_split(cmd->arg[coor[0]], '>')[0];
	else
		file->fd_file = ft_strdup(cmd->arg[coor[0] + 1]);
	file->fd_file = reset_quote(file->fd_file);
}

void	choose_parsing(t_cmd *cmd, t_file *file, char *line, int coor[2])
{
	while (cmd->arg[coor[0]])
	{
		coor[1] = 0;
		while (cmd->arg[coor[0]][coor[1]])
		{
			if (cmd->arg[coor[0]][coor[1]] == '<' 
				&& cmd->arg[coor[0]][coor[1] + 1]
					&& cmd->arg[coor[0]][coor[1] + 1] == '<' )
				parsing_en_here_doc(cmd, file, coor, line);
			else if (cmd->arg[coor[0]][coor[1]] == '<')
				parsing_en(cmd, file, coor, line);
			if (cmd->arg[coor[0]][coor[1]] == '>' 
				&& cmd->arg[coor[0]][coor[1] + 1]
					&& cmd->arg[coor[0]][coor[1] + 1] == '>' )
				parsing_ex_append(cmd, file, coor, line);
			else if (cmd->arg[coor[0]][coor[1]] == '>')
				parsing_ex(cmd, file, coor, line);
			coor[1]++;
		}
		coor[0]++;
	}
}
