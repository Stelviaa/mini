/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:28:13 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 02:58:17 by sforesti         ###   ########.fr       */
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
