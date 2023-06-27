/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:25:01 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/27 08:00:08 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_command(t_cmd *cmd, char **envp, char *line)
{
	char	*command;

	command = str_lower(cmd->name);
	if (is_equal("echo", command))
		ft_echo(cmd->arg);
	else if (is_equal("pwd", command) && !cmd->arg[1])
		printf("%s\n", getcwd(NULL, 0));
	else if (is_equal("export", command))
		ft_export(envp, cmd->arg);
	else if (is_equal("env", command) && !cmd->arg[1])
		ft_env(envp);
	else if (is_equal("exit", command))
		ft_exit(envp);
	else if (is_equal("unset", command))
		ft_unset(cmd->arg, envp);
	else if (is_equal("cd", command))
		ft_cd(cmd->arg[1], envp);
	else
	{	
		exec_cmd(cmd, envp, line);
		if (!count_pipe(line))
			wait(NULL);
	}
}

char	*ft_strmup(const char *s1)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	if (!s1)
	{
		ret = malloc(sizeof(char));
		ret[0] = '\0';
		return (ret);
	}
	len = ft_strlen(s1);
	ret = malloc(sizeof(char) * len + 1);
	if (ret == 0)
		return (0);
	while (i < len)
	{
		ret[i] = s1[i];
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_getenv(char **envp, char *str)
{
	int		i;
	int		o;
	char	**line;

	i = -1;
	while (envp[++i])
	{
		o = 0;
		line = ft_split(envp[i], '=');
		while (line[o])
			o ++;
		if (o > 1)
		{
			o = 2;
			while (line[o])
			{	
				line[1] = ft_strjoin(ft_strjoin_f(line[1], "=", 1), line[o]);
				o ++;
			}
		}
		if (!ft_strncmp(line[0], str, ft_strlen(line[0]))
			&& !ft_strncmp(line[0], str, ft_strlen(str)))
			return (line[1]);
	}
	return (0);
}

char	**pre_process(char **str, char **envp)
{
	int		i;
	int		y;
	char	**ret;

	i = -1;
	y = 1;
	while (str[++i])
	{
		if (is_in(str[i], '$'))
		{
			ret = ft_split(str[i], '$');
			if (str[i][0] == '$')
				str[i] = ft_strmup(ft_getenv(envp, ret[0]));
			else
				str[i] = ft_strmup(ret[0]);
			while (ret[y])
			{
				str[i] = ft_strjoin_f(str[i], ft_getenv(envp, ret[y]), 1);
				y ++;
			}
			y = 1;
		}
	}
	return (str);
}

void	interrupt(int i)
{
	(void)i;
	kill(-15, SIGINT);
	write(1, "\b", 1);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	quit(int i)
{
	(void)i;
	if (glob == 1)
	{
		write(1, "\b", 1);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_ctrl()
{
	struct termios	new;

	tcgetattr(0, &new);
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new);
}

int	main(int ac, char **av, char **envp)
{
	char		*oui;

	(void) ac;
	(void) av;
	oui = getcwd(NULL, 0);
	signal(SIGINT, interrupt);
	signal(SIGQUIT, quit);
	while (oui != 0)
	{
		glob = 0;
		oui = readline("Minishell>");
		if (oui && *oui)
		{
			add_history(oui);
			manage_exec(oui, envp);
		}	
	}
	return (0);
}
