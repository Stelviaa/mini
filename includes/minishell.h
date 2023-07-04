/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:44:13 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/04 20:30:47 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <libft.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <termios.h>

typedef struct s_file {
	int				type;
	char			*fd_file;
	struct s_file	*next;
}				t_file;

typedef struct s_cmd {
	char			*name;
	char			**arg;
	int				fd[2];
	int				here_doc;
	t_file			*file;
	struct s_cmd	*next;
}				t_cmd;

int glob;

void	ft_echo(char **str);
void	ft_env(char **envp);
int		is_in(char *str, char c);
int		is_equal(char *search, char *str);
void	ft_exit(char **envp, char *arg);
void	ft_export(char **envp, char **str);
void	ft_unset(char **name, char **envp);
void	ft_cd(char *path, char **envp);
char	**split_path(char **envp);
char	*acces_cmd(char **envp, char *cmd);
char	*ft_quote(char *str);
void	free_dptr(char	**dptr);
void	exec_cmd(t_cmd *cmd, char **envp, char *line);
char	*str_lower(char *str);
void	rl_replace_line(const char *text, int clear_undo);
int		count_pipe(char *line);
char	**pre_process(char **str, char **envp);
char	**ft_split_parse(char const *s, char c);
int		manage_pipe(t_cmd *cmd, char **envp, char *line);
void	get_command(t_cmd *cmd, char **envp, char *line);
int		size_dptr(char **str);
t_cmd	*init_cmd_pipe(char *line, char **envp);
void	cmd_with_path(t_cmd *cmd, char	*path, char **envp);
char	*join_path(char **str);
t_cmd	*init_cmd_basic(t_cmd *cmd, char *line, char **envp);
int		find_name(char	**str, int mode);
t_cmd	*manage_cmd(char *line, char **envp);
void	manage_exec(char *line, char **envp);
t_cmd	*parse_path(t_cmd *cmd, char *path);
void	exec_for_pipe(t_cmd *cmd, char **envp);
int		create_infile(char *limiter);
void	redirect_ex_cmd_basic(t_file *file);
void	redirect_en_cmd_basic(t_file *file);
char	*ft_union(char	**str);
t_cmd	*parsed_line(char *line, char **envp);
void	manage_redirec(char **envp, t_cmd *cmd, char *line);
t_file	*init_tfile(char *line);
char	*reset_quote(char *str);
void	redirection(t_file *file);

#endif