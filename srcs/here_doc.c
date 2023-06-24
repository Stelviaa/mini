/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:29:31 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/13 13:31:27 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_infile(t_cmd *gnl, char *limiter)
{
	char	*line;
	char	*str;

	str = ft_calloc(1, 1);
	limiter = ft_strjoin_f(limiter, ft_strdup("\n"), 3);
	if (pipe(gnl->fd_hd) == -1)
		perror("Minishell: HereDoc: ");
	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(0);
		if (!ft_strcmp(line, limiter))
			break ;
		str = ft_strjoin_f(str, line, 3);
	}
	free (line);
	str = ft_strjoin_f(str, ft_strdup("\0"), 3);
	write (gnl->fd_hd[1], str, ft_strlen(str));
	free(str);
	free(limiter);
	gnl->in_fd = dup(gnl->fd_hd[0]);
	close(gnl->fd_hd[0]);
	close(gnl->fd_hd[1]);
	return ;
}
