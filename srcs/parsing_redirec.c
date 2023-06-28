/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 08:15:45 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/28 20:15:45 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_name(char	**str, int mode)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (str[++i])
	{
		while (str[i][++j])
		{
			if (str[i][j] == '<' && mode == 1)
				return (i + 1);
			if (str[i][j] == '>' && mode == 2)
				return (i + 1);
		}
		j = -1;
	}
	return (-1);
}

/*char	**redirec_format(char **arg)
{
	char	**ret;
	int		i;

	i = 0;
	while (arg[i])
		i ++;
	if ()
	ret = malloc(sizeof(char * ));
	if (find_name(arg, 1) != -1)
	{

	}

}*/


t_file	*init_tfile(char *line)
{
	t_file	*file;

	(void)line;
	file = malloc(sizeof(t_file));
	file->fd_file_in = 0;
	file->fd_file_out = 0;
	return (file);
}

void	manage_redirec(char **envp, t_cmd *cmd, char *line)
{
	int	i;

	(void)envp;
	(void)line;
	cmd->file = init_tfile(line);
	if ((find_name(cmd->arg, 1)) && cmd->arg[1])
	{
		i = find_name(cmd->arg, 1);
		if (i != -1 && ft_strlen(cmd->arg[i - 1]) > 1)
			cmd->file->fd_file_in = ft_split(cmd->arg[i - 1], '<')[0];
		else if (i != -1)
			cmd->file->fd_file_in = cmd->arg[i];
	}
	if ((find_name(cmd->arg, 2)) && cmd->arg[1])
	{
		i = find_name(cmd->arg, 2);
		if (i != -1 && ft_strlen(cmd->arg[i - 1]) > 1)
			cmd->file->fd_file_out = ft_split(cmd->arg[i - 1], '>')[0];
		else if (i != -1)
			cmd->file->fd_file_out = cmd->arg[i];
	}
}
