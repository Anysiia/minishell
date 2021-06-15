/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:04:56 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/15 11:27:22 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <stdarg.h>
# include <errno.h>
# include <limits.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include "../libft/libft.h"
# include "define.h"
# include "struct.h"

/*
BUILTINS
*/

int		cd_builtin(int ac, char **av, t_minishell *minishell);
int		echo_builtin(int ac, char **av, t_minishell *minishell);
int		pwd_builtin(int ac, char **av, t_minishell *minishell);
int		export_builtin(int ac, char **av, t_minishell *minishell);
int		env_builtin(int ac, char **av, t_minishell *minishell);
int		unset_builtin(int ac, char **av, t_minishell *minishell);
int		exit_builtin(int ac, char **av, t_minishell *minishell);
int		is_directory(const char *path);
int		print_sort_env(char **env);

/*
ENV UTILS
*/

void	create_env(t_minishell *minishell, char **envp);
char	*ft_getenv(char **env, const char *name);
int		ft_putenv(t_minishell *minishell, char *string);
int		ft_setenv(t_minishell *msh, const char *name, const char *val, int rep);
char	*join_var(const char *s1, const char *s2, const char *s3);
int		ft_unsetenv(t_minishell *minishell, const char *name);
int		ft_clearenv(char **env);
char	**dup_env(char **env, size_t len, int erase);
size_t	len_name_env(const char *name);
int		find_variable_index(char **env, const char *name);
int		find_variable_name(char **name, const char *string);
int		find_variable_value(char **value, const char *string);
int		ft_printenv(char **env);
int		set_pwd(t_minishell *minishell, const char *env_name);

/*
EXEC
*/

int		execute_command(t_minishell *minishell, t_cmd *command);
void	default_fd(int fd[2]);
void	manage_redir(t_cmd *command, int fd[2]);

/*
UTILS
*/

void	register_signal(t_minishell *minishell);
void	print_prompt(char **env);
int		save_state(bool action, int state);
void	set_state(int state);
int		get_state(void);
int		save_exit(bool action, int exit);
void	set_exit(int exit);
int		get_exit(void);
int		save_lexer(bool action, int lexer);
void	set_lexer(int lexer);
int		get_lexer(void);
void	exit_shell(t_minishell *minishell);
int		is_quote(const char c);
char	*expand_token_word(char **env, char *word);
void	remove_backslash(char **new_word, const char *word, int *i);
void	remove_quote(char **env, char **new_word, const char *word, int *i);
void	get_var_value(char **env, char **new_word, const char *word, int *i);

/*
ERRORS
*/

void	exit_error(t_minishell *minishell, const char *msg);
void	error_lexer(const char *error, bool quit);
void	print_error(const char *msg, bool quit);
void	print_errno(const char *error_command);
void	print_exec_error(const char *error_command, const char *msg);
void	builtin_usage(const char *command_name, const char *error);
int		builtin_error(const char *cmd, const char *arg, const char *er, int st);
int		invalid_id(const char *command_name, const char *variable_name);
int		invalid_option(const char *command_name, const char *option);
int		argument_error(const char *command_name);

/*
PARSER
*/

t_token	create_token(const char *s, t_token_type tok_type);
t_token	*malloc_token(const char *s, t_token_type tok_type);
void	delete_first_token(t_token *tokens);
void	delete_all_tokens(t_token **tokens);
void	create_lexer(t_lexer *lexer);
t_lexer	*malloc_lexer(void);
void	reset_lexer(t_lexer *lexer);
void	free_lexer(t_lexer	*lexer);
int		split_into_tokens(t_lexer *lexer);
void	print_lexer(t_lexer *lexer);
char	*handle_quote(char *word, t_lexer *lexer);
void	handle_metacharacter(t_lexer *lexer);
char	*append_char_to_str(char *str, char c);
void	add_token(t_lexer *lexer, char *s, int type);
t_cmd	*malloc_command(void);
void	free_command(t_cmd **cmd);
void	find_command(char **env, t_cmd *cmd);
int		is_builtin(t_cmd *cmd);
char	*expand_relative_path(char **env, t_cmd *cmd);
int		is_file(const char *name);
int		parse_tokens(t_minishell *minishell);
void	create_new_command(t_minishell *minishell, t_token *list);
bool	is_redir(t_token *token);

#endif
