/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:28:13 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/04 16:28:45 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cutenv(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '=')
		i ++;
	ret = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		ret[i] = str[i];
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}

int	is_env(char	*env, char	*str)
{
	char	*strr;
	char	*envr;
	int		i;

	strr = ft_cutenv(str);
	envr = ft_cutenv(env);
	i = (ft_strncmp(strr, envr, ft_strlen(strr)) == 0
			&& ft_strncmp(strr, envr, ft_strlen(envr)) == 0);
	free(strr);
	free(envr);
	return (i);
}

void	ft_export2(char **envp, char **str, int i, int y)
{
	while (envp[i] && !is_env(envp[i], str[y]))
	{
		i ++;
	}
	if (envp[i])
		envp[i] = ft_strdup(str[y]);
	else
	{
		envp[i] = ft_strdup(str[y]);
		envp[i + 1] = 0;
	}
}

void	ft_export(char **envp, char **str)
{
	int		i;
	int		y;

	y = 1;
	i = 0;
	if (str[1] == 0)
	{
		while (envp[i])
		{
			printf("declare -x %s\n", ft_quote(envp[i]));
			i ++;
		}
		return ;
	}
	while (str[y])
	{
		if (ft_isalpha(str[y][0]))
			ft_export2(envp, str, i, y);
		else
			printf("minishell: export: `%s': not a valid identifier\n", str[y]);
		y ++;
	}
}

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (is_in(envp[i], '='))
			printf("%s\n", envp[i]);
		i ++;
	}
}

int	index_env(char *name, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (is_env(name, envp[i]))
			return (i);
		i ++;
	}
	return (-1);
}

void	ft_unset(char **name, char **envp)
{
	int	i;
	int	y;

	y = 1;
	while (name[y])
	{
		i = index_env(name[y], envp) + 1;
		while (i != -1 && envp[i])
		{
			envp[i - 1] = envp[i];
			i ++;
		}
		if (i != -1)
			envp[i - 1] = 0;
		y ++;
	}
}

void	go_home(char	**envp)
{
	int y;
	int i;
	int u;
	char	*path;

	i = 5;
	u = 0;
	y = index_env(ft_strdup("OLDPWD"), envp);
	envp[y] = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(getcwd(NULL, 0)));
	y = index_env(ft_strdup("HOME"), envp);
	path = malloc(sizeof(char) * ft_strlen(envp[y]) - 4);
	while (envp[y][i])
	{
		path[u] = envp[y][i];
		u ++;
		i ++;
	}
	path[u] = '\0';
	chdir(path);
	y = index_env(ft_strdup("PWD"), envp);
	envp[y] = ft_strjoin(ft_strdup("PWD="), ft_strdup(getcwd(NULL, 0)));
	return;
}

void	ft_cd(char *path, char **envp)
{
	DIR	*i;
	int	y;

	if (path == NULL)
	{
		go_home(envp);
		return ;
	}
	if ((path[0] == 34 || path[0] == 39) && !path[1])
		return ;
	i = opendir(path);
	if (i == NULL)
	{
		perror(ft_strjoin_f("Minishell: cd: ", path, 4));
		return ;
	}
	y = index_env(ft_strdup("OLDPWD"), envp);
	envp[y] = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(getcwd(NULL, 0)));
	chdir(path);
	y = index_env(ft_strdup("PWD"), envp);
	envp[y] = ft_strjoin(ft_strdup("PWD="), ft_strdup(getcwd(NULL, 0)));
}
