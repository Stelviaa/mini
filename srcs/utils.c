/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:24:07 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/23 17:06:44 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

int	is_equal(char *search, char *str)
{
	int	i;

	i = 0;
	while (search[i])
	{
		if (str[i] != search[i])
			return (0);
		i ++;
	}
	if (str[i])
		return (0);
	return (1);
}

void	ft_exit(char **envp)
{
	int	i;

	i = 0;
	if (envp && envp[1])
		i = ft_atoi(envp[1]) % 256;
	printf("exit\n");
	exit (i);
}

char	*ft_quote(char *str)
{
	int		i;
	int		off;
	char	*ret;

	off = 0;
	i = 0;
	while (str[i])
		i ++;
	ret = malloc(sizeof(char) * (i + 3));
	i = 0;
	while (str[i])
	{
		ret[i + off] = str[i];
		if (str[i] == '=')
		{
			off ++;
			ret[i + off] = '"';
		}
		i ++;
	}
	if (off > 0)
		ret[i + off] = '"';
	ret[i + off + 1] = '\0';
	return (ret);
}

int	is_strnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i ++;
	}
	return (1);
}

char	*str_lower(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i])
		i ++;
	ret = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		ret[i] = ft_tolower(str[i]);
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_union(char	**str)
{
	int		len;
	int		i;
	char	*ret;

	i = find_name(str, 1) - 1;
	len = -1;
	if (i == 0)
	{
		if (ft_strlen(str[0]) > 1)
			len = 0;
		else
			len = 1;
	}
	ret = ft_strdup("");
	while (((++len < i) && i != 0) || (str[len] && !i))
	{
		ret = ft_strjoin_f(ft_strjoin_f(ret, str[len], 4), " ", 4);
	}
	return (ret);
}
