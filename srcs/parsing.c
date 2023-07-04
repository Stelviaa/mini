/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:50:17 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/04 17:36:37 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*reset_quote(char *str)
{
	int		i;
	int		j;
	int		quote;
	char	*ret;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == 34 || str[i] == 39))
		{
			quote = str[i];
			j ++;
		}
		else if (quote == str[i])
		{	
			quote = 0;
			j ++;
		}
		i ++;
	}
	ret = malloc(sizeof(char) * (i - j) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!quote && (str[i] == 34 || str[i] == 39))
		{
			quote = str[i];
			i ++;
		}
		else if (quote == str[i])
		{	
			quote = 0;
			i ++;
		}
		ret[j] = str[i];
		if (str[i])
		{
			i ++;
			j ++;
		}
	}
	ret[j] = 0;
	free(str);
	return (ret);
}

void	get_commands(char *line, t_cmd *cmd, char **envp)
{
	char	**cmds;
	int		i;
	char	*lines;

	i = 0;
	cmds = ft_split_parse(line, '|');
	lines = NULL;
	while (cmds[i])
	{
		cmd->arg = ft_split_parse(cmds[i], ' ');
		cmd->here_doc = 0;
		if (find_name(cmd->arg, 1) != -1 || find_name(cmd->arg, 2) != -1)
		{
			manage_redirec(envp, cmd, line);
			lines = ft_union(cmd->arg);
			free_dptr(cmd->arg);
			cmd->arg = ft_split(lines, ' ');
		}
		pre_process(cmd->arg, envp);
		cmd->name = acces_cmd(envp, cmd->arg[0]);
		if (cmds[i + 1])
		{
			cmd->next = malloc(sizeof(t_cmd));
			cmd = cmd->next;
			cmd->file = 0;
		}
		i ++;
	}
	cmd->next = 0;
}

t_cmd	*parsed_line(char *line, char **envp)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->file = 0;
	get_commands(line, cmd, envp);
	return (cmd);
}
