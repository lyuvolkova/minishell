/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 00:49:20 by lubov             #+#    #+#             */
/*   Updated: 2022/04/12 00:12:48 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <signal.h>
# include "ft_structs.h"
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

int		ft_env(t_list *lexer, int pipe, char **envp);
int		ft_exit(t_list *lexer, int pipe);
int		ft_cd(t_list *lexer, int pipe);
int		ft_pwd(t_list *lexer, int pipe);
int		ft_echo(t_list *lexer, int pipe);
int		ft_unset(t_list *lexer, int pipe, char **envp);
int		ft_export(t_list *lexer, int pipe, char ***envp);

void	get_signal(int sig);
int		parsing(char *buf, t_list *lexer);
int		fill_lexer(char *input, t_list **lexer);
void	free_lexer(t_list *lexer);
void	get_new_lexer(t_list *lexer);
int		not_interpret(t_list *lexer);

void	which_quotes(t_list *lexer);
void	replace_var_env(t_list *lexer);
int		check_error(t_list *lexer);
void	which_pipe(t_list *lexer);
void	is_option(t_list *lexer);
void	free_str(t_list *lexer);

int		is_str_a_nbr(char *str);
int		count_pipes(t_list *lexer);
int		env_too_much_args(t_list *lexer, int pipe);

void	ft_pipex(t_list *lexer);
void	exec_cmd(t_list *lexer, int pipe, char ***envp);
char	*check_bin(char *bin, char *cmd);
char	**args_into_str(t_list *lexer, int pipe);
char	*strjoin_path(char const *s1, char const *s2);
char	*ft_strnew(size_t size);
void	ft_free_str(char **arr);
char	*ft_strjoinch(char const *s1, char c);
int		ft_str_swith(char *s1, char *s2);

char	**split_quotes(char *s);
int		lexing_quotes(char **input);
void	print_lexer(t_list *lexer);
void	init_vec(t_vec *cpt);
char	*ft_strdupn(char *s, int n);

int		check_args(t_list *lexer, int pipe);
int		ft_process(char *path, char **args);
//redir
int		redirection(t_list *lexer, int pipe, char ***envp);
void	skip_heredoc(char *delim);
void	create_file_out(char *name);
void	create_file_appen(char *name);
char	*get_env_var(char *var);
char	**ft_new_split(char *s);
int		check_fd_in(char *name);
int		redir_in(char *name, int pipe, t_list *lexer, char ***envp);
void	redir_appen(char *name, int pipe, t_list *lexer, char ***envp);
void	redir_heredoc(char *delim, int pipe, t_list *lexer, char ***envp);
int		redir_in_out(t_fds *fds, int pipe, t_list *lexer, char ***envp);
int		redir_in_appen(t_fds *fds, int pipe, t_list *lexer, char ***envp);
void	redir_out(char *name, int pipe, t_list *lexer, char ***envp);
void	redir_heredoc_appen(t_fds *fds, int pipe, t_list *lexer, char ***envp);
void	redir_heredoc_out(t_fds *fds, int pipe, t_list *lexer, char ***envp);
void	redir_heredoc(char *delim, int pipe, t_list *lexer, char ***envp);
void	heredoc_while(char *delim);
//parse
void	is_fd(t_list *lexer);
void	is_cmd(t_list *lexer);
int		syntax_error(t_list *lexer);
//utils
void	ft_lstadd_back(t_list **alst, t_list *new);
void	free_split(char **s);
char	*rejoin_the_split(char **s);
void	init_fds(t_fds *fds);
void	find_the_last(t_list *lexer, int pipe, t_fds *fds);
t_list	*while_pipe(int pipe, t_list *lexer);
int		isvalid_export(char *line);
void	add_key_envp(char ***envp, char *cmd, int keyindex);
int		check_key(char **envp, char *line);
int		is_valid_key(char *key);
char	**sort_env(char **envp);
int		count_envp_row(char **envp);
//env
char	**copy_envp(char **envs);
int		have_equal(char *line);
void	print_quote(char *str, int fd);
void	print_export(char **envp, int fd);
int		add_envp(char *cmd, char ***envp);

//exit
void	exit_succes(t_list *lexer);
void	free_all(t_list *lexer);

//error
int		new_int_error(char *cmd, char *arg, char *msg, int fd);
int		cmd_error(char *cmd, char *msg, int fd);
int		error_bool(char *cmd, char *arg, char *msg, int fd);
void	free_array(char **array);

#endif