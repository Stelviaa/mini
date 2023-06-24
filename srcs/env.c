/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:28:13 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/24 11:55:36 by luxojr           ###   ########.fr       */
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
	//char	*name_e;

	i = 0;
	//name_e = ft_strjoin(name, ft_strdup("="));
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

void	ft_cd(char *path, char **envp)
{
	int	i;
	int	y;

	i = access(path, F_OK);
	if (i == -1)
	{
		strerror(errno);
		//perror("Minishell: cd:");
		//perror(path);
		return ;
	}
	y = index_env(ft_strdup("OLDPWD"), envp);
	envp[y] = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(getcwd(NULL, 0)));
	chdir(path);
	y = index_env(ft_strdup("PWD"), envp);
	envp[y] = ft_strjoin(ft_strdup("PWD="), ft_strdup(getcwd(NULL, 0)));
}
