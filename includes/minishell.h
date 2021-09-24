/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:04:56 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/24 17:38:33 by cmorel-a         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
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

void	execute_command(t_minishell *minishell, t_cmd *command);
void	execute_simple_command(t_minishell *minishell, t_cmd *command);
void	execute_pipe(t_minishell *minishell, t_cmd *command);
int		expand_token_word(char **env, t_cmd *command, int *i);
int		cat_c_to_str(t_expand *tmp, const char c);
int		up_expand_buffer(t_expand *tmp, int len_required);
int		expand_strong_quote(t_expand *tmp, const char *arg);
int		expand_weak_quote(t_expand *tmp, const char *arg, char **env);
int		expand_variable(t_cmd *cmd, t_expand *tmp, int *i, char **env);
int		get_last_exit_status(t_expand *tmp);
char	*get_variable_content(t_expand *tmp, const char *arg, char **env);
char	**insert_split_in_av(char **av, char **split, int index);
void	default_fd(int fd[2]);
void	manage_redir(t_cmd *command, int fd[2]);
void	close_fd(int fd);

/*
UTILS
*/

void	register_signal(t_minishell *minishell);
char	*create_prompt(char *prompt, char **env);
int		save_state(bool action, int state);
void	set_state(int state);
int		get_state(void);
int		save_exit(bool action, int exit);
void	set_exit(int exit);
int		get_exit(void);
void	exit_shell(t_minishell *minishell);
char	*append_c_to_str(char *new_word, char c);

/*
ERRORS
*/

void	exit_error(t_minishell *minishell, const char *msg);
void	error_lexer(const char *error, bool quit, int *lexer_state);
void	print_error(const char *msg, bool quit);
void	print_errno(const char *error_command);
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
int		split_into_tokens(t_lexer *lexer, int *lexer_state);
void	print_lexer(t_lexer *lexer);
char	*handle_quote(char *word, t_lexer *lexer, int *lexer_state);
void	handle_metacharacter(t_lexer *lexer, int *lexer_state);
char	*append_char_to_str(char *str, char c, int *lexer_state);
void	add_token(t_lexer *lexer, char *s, int type, int *lexer_state);
t_cmd	*malloc_command(void);
void	free_command(t_cmd **cmd);
void	find_command(char **env, t_cmd *cmd);
int		is_builtin(t_cmd *cmd);
char	*expand_relative_path(char **env, t_cmd *cmd);
int		is_file(const char *name);
int		parse_tokens(t_minishell *minishell, int *lexer_state);
void	create_new_command(t_minishell *minishell, t_token *list, int *lexer);
bool	is_redir(t_token *token);

#endif
