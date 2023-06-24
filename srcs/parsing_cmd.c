/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:20:37 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/23 17:07:38 by luxojr           ###   ########.fr       */
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

char	*parsing_redir_en_start(t_cmd *cmd, char *tmp)
{
	char	**tmp_two;
	char	*ret;

	tmp_two = ft_split_two(tmp, " <");
	cmd->redirec_en = 1;
	cmd->name_file = ft_strdup(tmp_two[0]);
	ret = ft_union(tmp_two, 1);
	return (ret);
}

char	*parsing_redir_en(t_cmd *cmd, char *tmp)
{
	char	**tmp_two;
	char	**tmp_dup;
	char	*line_dup;
	char	*ret;

	line_dup = ft_strdup(tmp);
	tmp_two = ft_split(tmp, ' ');
	tmp_dup = ft_split(tmp, '<');
	ret = ft_strdup(tmp_dup[0]);
	if (tmp_two[find_name(tmp_two, 1) - 1][0] == '<'
		&& tmp_two[find_name(tmp_two, 1) - 1][1] == '\0')
		cmd->redirec_en = 1;
	else if (tmp_two[find_name(tmp_two, 1) - 1][0] == '<'
		&& tmp_two[find_name(tmp_two, 1) - 1][1] == '<'
			&& tmp_two[find_name(tmp_two, 1) - 1][2] == '\0')
		cmd->redirec_en = 2;
	cmd->name_file
		= ft_strdup(ft_split(tmp_two[find_name(tmp_two, 1)], ' ')[0]);
	free_dptr(tmp_dup);
	free_dptr(tmp_two);
	free(line_dup);
	return (ret);
}

char	*parsing_redir_ex(t_cmd *cmd, char *tmp)
{
	char	**tmp_two;
	char	**tmp_dup;
	char	*line_dup;
	char	*ret;

	line_dup = ft_strdup(tmp);
	tmp_two = ft_split(ft_strdup(tmp), ' ');
	tmp_dup = ft_split(ft_strdup(tmp), '>');
	ret = ft_strdup(tmp_dup[0]);
	if (tmp_two[find_name(tmp_two, 2) - 1][0] == '>'
		&& tmp_two[find_name(tmp_two, 2) - 1][1] == '\0')
		cmd->redirec_ex = 1;
	else if (tmp_two[find_name(tmp_two, 2) - 1][0] == '>'
		&& tmp_two[find_name(tmp_two, 2) - 1][1] == '>'
			&& tmp_two[find_name(tmp_two, 2) - 1][2] == '\0')
		cmd->redirec_ex = 2;
	cmd->name_file
		= ft_strdup(ft_split(tmp_two[find_name(tmp_two, 2)], ' ')[0]);
	free_dptr(tmp_dup);
	free_dptr(tmp_two);
	free(line_dup);
	return (ret);
}

t_cmd	*choose_parsing(int is_pipe, t_cmd *cmd, char *tmp, char **envp)
{
	char	**tmp_cdt;

	tmp_cdt = ft_split(tmp, ' ');
	cmd->redirec_en = 0;
	cmd->redirec_ex = 0;
	cmd->name_file = NULL;
	if (find_name(tmp_cdt, 1) > 0)
	{
		if (tmp_cdt[0][0] == '<')
		{
			tmp = parsing_redir_en_start(cmd, tmp);
		}
		else
			tmp = parsing_redir_en(cmd, tmp);
	}
	else if (ft_strchr(tmp, '>'))
		tmp = parsing_redir_ex(cmd, tmp);
	if (ft_strchr(ft_split(tmp, ' ')[0], '/'))
		cmd = parse_path(cmd, tmp);
	else
		cmd = init_cmd_basic(cmd, tmp, envp);
	cmd->is_pipe = is_pipe;
	return (cmd);
}

t_cmd	*init_cmd_basic(t_cmd *cmd, char *line, char **envp)
{
	//int		i;

	//i = -1;
	cmd->arg = ft_split(line, ' ');
	cmd->name = ft_strdup(cmd->arg[0]);
	cmd->path = acces_cmd(envp, cmd->name);
	cmd->line = ft_strdup(line);
	cmd->next = 0;
	return (cmd);
}

char	**join_arg_path(char *path)
{
	char	**tmp_path;
	char	**tmp;
	char	**arg;
	int		i;
	int		j;

	i = 0;
	j = -1;
	tmp_path = ft_split(path, ' ');
	tmp = ft_split(ft_strdup(tmp_path[0]), '/');
	while (tmp[i + 1])
		i ++;
	while (tmp_path[j])
		j ++;
	arg = malloc(sizeof(char *) * (j + 1));
	arg[0] = ft_strdup(tmp[i]);
	i = 0;
	while (tmp_path[++i])
		arg[i] = ft_strdup(tmp_path[i]);
	arg[i] = NULL;
	return (arg);
}

t_cmd	*parse_path(t_cmd *cmd, char *path)
{
	int		i;
	char	*dup_path;
	char	**tmp;
	char	**new_path;

	i = 0;
	dup_path = ft_strdup(path);
	tmp = ft_split_two(dup_path, "/");
	while (tmp[i + 1])
		i++;
	cmd->arg = join_arg_path(ft_strdup(path));
	cmd->name = ft_strdup(cmd->arg[0]);
	new_path = ft_split(path, ' ');
	cmd->path = ft_strdup(new_path[0]);
	cmd->next = 0;
	free_dptr(tmp);
	free_dptr(new_path);
	return (cmd);
}

t_cmd	*init_cmd_pipe(char *line, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*cmd_begin;
	char	**tmp;
	int		is_pipe;
	int		i;

	i = -1;
	tmp = ft_split(line, '|');
	is_pipe = 0;
	if (tmp[1])
		is_pipe = 1;
	cmd = malloc(sizeof(t_cmd));
	cmd_begin = cmd;
	while (tmp[++i])
	{
		cmd = choose_parsing(is_pipe, cmd, tmp[i], envp);
		cmd->index = i;
		if (tmp[i + 1])
			cmd->next = malloc(sizeof(t_cmd));
		cmd = cmd->next;
	}
	free_dptr(tmp);
	cmd_begin->end = i;
	cmd = 0;
	return (cmd_begin);
}
