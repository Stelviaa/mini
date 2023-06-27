/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:57:20 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/27 08:01:33 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(char *line)
{
	int	i;
	int	nbr_pipe;
	int	quote;

	i = -1;
	nbr_pipe = 0;
	quote = 0;
	while (line[++i])
	{
		if ((line[i] == 39 || line[i] == 34) && quote == 0)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		if (line[i] == '|' && !quote)
			nbr_pipe ++;
	}
	return (nbr_pipe);
} 

int	redirection_exit(t_cmd *cmd)
{
	//int	fd;

	//fd = 0;
	if (cmd->next)
	{
		close(cmd->fd[0]);
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
	//}
	//else if (cmd->redirec_ex != 0)
		//redirect_ex_cmd_basic(cmd);
	return (0);
}

int	redirection_enter(t_cmd *cmd)
{
	//if (cmd->redirec_en == 0)
	//{
	dup2(cmd->fd[0], STDIN_FILENO);
	close (cmd->fd[0]);
	close (cmd->fd[1]);
	//}
	//if (cmd->redirec_en != 0)
		//redirect_ex_cmd_basic(cmd);
	return (0);
}

int	exec_pipe(t_cmd *cmd, char **envp, char *line)
{
	pid_t	pid;

	if (cmd->next)
		if (pipe(cmd->fd) == -1)
			return (-1);
	pid = fork();
	if (pid == 0)
	{
		if (cmd->next)
			redirection_exit(cmd);
		get_command(cmd, envp, line);
	}
	else
	{
		if (cmd->next)
			redirection_enter(cmd);
	}
	close (cmd->fd[1]);
	close (cmd->fd[0]);
	return (0);
}

int	manage_pipe(t_cmd *cmd, char **envp, char *line)
{
	int		stdin_fd;

	stdin_fd = dup(STDIN_FILENO);
	while (cmd)
	{
		exec_pipe(cmd, envp, line);
		cmd = cmd->next;
	}
	dup2(stdin_fd, 0);
	while (wait(NULL) > 0)
		;
	return (0);
}
