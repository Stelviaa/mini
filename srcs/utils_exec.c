/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:33:52 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/29 01:22:09 by luxojr           ###   ########.fr       */
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

void	redirect_en_cmd_basic(t_file *file)
{
	int	fd;

	fd = 0;
	if (file->type == 1)
	{
		fd = open (file->fd_file, O_RDONLY);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			exit (0);
		}
		dup2(fd, STDIN_FILENO);
	}
	if (file->type == 3)
	{
		fd = create_infile(file->fd_file);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			exit (0);
		}
		dup2(fd, STDIN_FILENO);
	}
}

void	redirect_ex_cmd_basic(t_file *file)
{
	int	fd;

	fd = 0;
	if (file->type == 2)
	{
		fd = open (file->fd_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			exit(0);
		}
		dup2(fd, STDOUT_FILENO);
	}
	if (file->type == 4)
	{
		fd = open (file->fd_file, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			exit(0);
		}
		dup2(fd, STDOUT_FILENO);
	}
}

void	exec_cmd(t_cmd *cmd, char **envp, char *line)
{
	pid_t	pid;
	int		status;

	pid = 0;
	(void) line;
	if (!count_pipe(line))
		pid = fork();
	if (pid == 0)
	{
		glob = 1;
		while (cmd->file)
		{
			redirect_en_cmd_basic(cmd->file);
			redirect_ex_cmd_basic(cmd->file);
			cmd->file = cmd->file->next;
		}
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
