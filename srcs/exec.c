/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:07:17 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/22 14:02:20 by sforesti         ###   ########.fr       */
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

	cmd = init_cmd_pipe(line, envp);
	/*while (cmd)
	{
		printf ("===================\ncmd->path: %s\ncmd->name: %s\ncmd->index: %d\ncmd->is_pipe: %d\n", cmd->path, cmd->name, cmd->index, cmd->is_pipe);
		printf("cmd->redirec_enter: %d\nredirec_exit: %d\nname_file: %s\n", cmd->redirec_en, cmd->redirec_ex, cmd->name_file);
		printf("cmd->arg: ");
		for(int i = 0; cmd->arg[i]; i++)
			printf("%s ", cmd->arg[i]);
		printf("\n");
		cmd = cmd->next;
	}*/
	if (cmd->is_pipe)
		manage_pipe(cmd, envp);
	else
		get_command(cmd, envp);
}
