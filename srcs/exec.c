/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:07:17 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/28 20:07:11 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(char **str)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_strjoin_f(str[0], " ", 4);
	while (str[++i])
	{
		line = ft_strjoin_f(line, str[i], 1);
		line = ft_strjoin_f(line, " ", 1);
	}
	return (line);
}

void	manage_exec(char *line, char **envp)
{
	t_cmd	*cmd;

	//if (find_name(cmd->arg, 1) != -1 || find_name(cmd->arg, 2) != -1)
	//cmd = manage_redirec(envp, line);
	cmd = parsed_line(line, envp);
	if (cmd->arg[0][0] == 0)
		return ;
	if (cmd->next)
		manage_pipe(cmd, envp, line);
	else
		get_command(cmd, envp, line);
}
