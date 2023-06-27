/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:01:47 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/26 16:34:18 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_charset(char const s, char c)
{
	return (c == s);
}	

int	ft_size_strs(char const *s, char c)
{
	int	i;
	int	j;
	int	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (s[i])
	{
		while (ft_is_charset(s[i], c) && s[i])
			i ++;
		if (!ft_is_charset(s[i], c) && s[i])
		{
			j ++;
			while ((!ft_is_charset(s[i], c) || quote) && s[i])
			{
				if ((s[i] == 39 || s[i] == 34) && quote == 0)
					quote = s[i];
				else if (s[i] == quote)
					quote = 0;
				i++;
			}
		}
	}
	return (j);
}

char	*ft_fill_str(char const *s, int start, int end)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (0);
	i = 0;
	while (start < end)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char	**ft_fill(char const *s, char c, char **r_str, int verif)
{
	int	i;
	int	j;
	int	start;
	int	quote;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	j = 0;
	quote = 0;
	while (s[i] && !verif)
	{
		start = i;
		while (s[i] && (!ft_is_charset(s[i], c) || quote))
		{
			if ((s[i] == 39 || s[i] == 34) && quote == 0)
				quote = s[i];
			else if (s[i] == quote)
				quote = 0;
			i++;
		}
		end = i;
		while (s[i] && ft_is_charset(s[i], c))
			i++;
		r_str[j] = ft_fill_str(s, start, end);
		j ++;
	}
	r_str[j] = 0;
	return (r_str);
}

char	**ft_split_parse(char const *s, char c)
{
	char	**r_str;
	int		i;
	int		verif;

	i = 0;
	verif = 0;
	if (!s)
		return (0);
	r_str = malloc(sizeof(char *) * (ft_size_strs(s, c) + 1));
	if (!r_str)
		return (0);
	while (s[i] == c)
		i++;
	if (!s[i])
		verif = 1;
	r_str = ft_fill(s, c, r_str, verif);
	return (r_str);
}
