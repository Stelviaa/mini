/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:57:20 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/26 18:45:28 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(char *line)
{
	int	i;
	int	nbr_pipe;

	i = -1;
	nbr_pipe = 0;
	while (line[++i])
	{
		if (line[i] == '|')
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

int	exec_pipe(t_cmd *cmd, char **envp)
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
		get_command(cmd, envp);
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

int	manage_pipe(t_cmd *cmd, char **envp)
{
	//int		nbr_cmd;
	int		stdin_fd;

	stdin_fd = dup(STDIN_FILENO);
	//nbr_cmd = cmd->end;
	(void) envp;
	//cmd->in_fd = 0;
	//cmd->out_fd = 0;
	while (cmd)
	{
		//if (cmd->index == 0 && cmd->redirec_en == 1)
		//{
			//cmd->in_fd = open(cmd->name_file, O_RDWR);
			//dup2(cmd->in_fd, STDIN_FILENO);
		//}
		exec_pipe(cmd, envp);
		//printf("%s\n%s====\n",cmd->name, cmd->arg[0]);
		cmd = cmd->next;
	}
	dup2(stdin_fd, 0);
	while (wait(NULL) > 0)
		;
	//if (cmd->in_fd)
		//close (cmd->in_fd);
	//if (cmd->out_fd)
		//close (cmd->out_fd);
	return (0);
}
