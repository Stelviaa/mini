/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:50:17 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/27 09:37:00 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_commands(char *line, t_cmd *cmd, char **envp)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = ft_split_parse(line, '|');
	while (cmds[i])
	{
		cmd->arg = ft_split_parse(cmds[i], ' ');
		pre_process(cmd->arg, envp);
		cmd->name = acces_cmd(envp, cmd->arg[0]);
		if (cmds[i + 1])
		{
			cmd->next = malloc(sizeof(t_cmd));
			cmd = cmd->next;
		}
		//printf("%s\n", cmd->name);
		i ++;
	}
	cmd->next = 0;
}

t_cmd	*parsed_line(char *line, char **envp)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	get_commands(line, cmd, envp);
	return (cmd);
}
