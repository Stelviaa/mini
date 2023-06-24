/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:26:40 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/08 11:09:54 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal_n(char *search, char *str)
{
	int	i;

	i = 0;
	while (search[i])
	{
		if (str[i] != search[i])
			return (0);
		i ++;
	}
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i ++;
	}
	return (1);
}

void	ft_echo(char **str)
{
	int	i;
	int	last;

	i = 0;
	last = 1;
	if (str[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (is_equal_n("-n", str[1]))
	{
		i ++;
		last = 0;
	}
	while (str[++i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
	}
	if (last)
		printf("\n");
}
