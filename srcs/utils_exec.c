/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:33:52 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/27 08:05:07 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dptr(char	**dptr)
{
	int	i;

	i = -1;
	while (dptr[++i])
		free(dptr[i]);
	free(dptr);
}

char	*acces_cmd(char **envp, char *cmd)
{
	char	**path;
	char	*tmp_path;
	int		i;

	i = -1;
	(void)envp;
	if (!access(cmd, F_OK) && ft_strchr(cmd, '/'))
		return (cmd);
	path = ft_split(getenv("PATH"), ':');
	while (path[++i])
		path[i] = ft_strjoin_f(path[i], ft_strdup("/"), 3);
	i = -1;
	while (path[++i])
	{
		tmp_path = ft_strjoin_f(path[i], cmd, 4);
		if (!access(tmp_path, F_OK))
		{
			free_dptr(path);
			return (tmp_path);
		}
		free (tmp_path);
	}
	free_dptr(path);
	return (cmd);
}

/*void	redirect_en_cmd_basic(t_cmd *cmd)
{
	int	fd;

	fd = 0;
	if (cmd->redirec_en == 1)
	{
		fd = open (cmd->name_file, O_RDONLY);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", cmd->name_file, 4));
			exit (0);
		}
		dup2(fd, STDIN_FILENO);
	}
	if (cmd->redirec_en == 2)
	{
		create_infile(cmd, cmd->name_file);
		//cmd->fd_hd = open ("fd_hd", O_RDWR);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", cmd->name_file, 4));
			exit (0);
		}
		dup2(cmd->in_fd, STDIN_FILENO);
	}
}*/

/*void	redirect_ex_cmd_basic(t_cmd *cmd)
{
	int	fd;

	fd = 0;
	if (cmd->redirec_ex == 1)
	{
		fd = open (cmd->name_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", cmd->name_file, 4));
			exit(0);
		}
		dup2(fd, STDOUT_FILENO);
	}
	if (cmd->redirec_ex == 2)
	{
		fd = open (cmd->name_file, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", cmd->name_file, 4));
			exit(0);
		}
		dup2(fd, STDOUT_FILENO);
	}
}*/

void	exec_cmd(t_cmd *cmd, char **envp, char *line)
{
	pid_t	pid;
	int		status;

	pid = 0;
	if (!count_pipe(line))
		pid = fork();
	if (pid == 0)
	{
		glob = 1;
		/*if (cmd->next)
		{
			redirect_en_cmd_basic(cmd);
			redirect_ex_cmd_basic(cmd);
		}*/
		status = execve(cmd->name, cmd->arg, envp);
		if (status == -1)
		{
			ft_putstr_fd(ft_strjoin_f(ft_strjoin_f("Minishell: ", cmd->arg[0], 4), ": command not found\n", 1), 2);
			exit(0);
		}
	}
}

int	size_dptr(char **str)
{
	int	i;

	i = -1;
	while (str[i])
		i++;
	return (i);
}
