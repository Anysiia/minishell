/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:27:33 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/09 17:13:26 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "define.h"
# include "struct.h"

extern int	g_state;
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
int		change_directory(t_minishell *minishell, const char *path);
int		go_directory(t_minishell *minishell, const char *variable_name);
void	cd_minus(t_minishell *minishell);

/*
ENVP UTILS
*/

char	*ft_getenv(t_env *envp, const char *name);
int		ft_setenv(t_minishell *msh, char *name, char *value, bool join);
int		ft_unset(t_minishell *minishell, const char *name);
void	init_minishell(t_minishell *minishell, char **envp);
void	push_back_var(t_minishell *minishell, char *name, char *value);
void	free_node(t_env *tmp);
void	free_envp(t_env **env);
void	convert_env_list_in_tab(t_minishell *minishell);
size_t	len_name_env(const char *name);

/*
EXEC
*/

void	execute_command(t_minishell *minishell, t_cmd *command);
void	execute_pipe(t_minishell *minishell, t_cmd *command);
void	execve_cmd(t_minishell *minishell, t_cmd *cmd);
int		expand_token_word(t_env *envp, t_cmd *command, int *i);
int		init_expand(t_expand *expand);
int		cat_c_to_str(t_expand *tmp, const char c);
int		up_expand_buffer(t_expand *tmp, int len_required);
int		expand_quote(t_expand *tmp, const char *arg, t_env *env);
int		expand_tilde(t_expand *tmp, const char *arg, t_env *envp);
int		expand_variable(t_cmd *cmd, t_expand *tmp, int *i, t_env *env);
int		get_last_exit_status(t_expand *tmp);
char	*get_variable_content(t_expand *tmp, const char *arg, t_env *env);
int		char_var(int c);
char	**insert_split_in_av(char **av, char **split, int index);
void	handle_error_redir(t_cmd *cmd);
int		redir_file(t_cmd *cmd, int *fd, int fdd, int nb_cmd);
void	default_fd(t_minishell *minishell);
void	close_fd(int fd);

/*
UTILS
*/

void	register_signal(t_minishell *minishell);
void	exec_signal(t_minishell *minishell);
int		interrupt_by_signal(void);
void	handle_signal_error(t_minishell *minishell);
char	*create_prompt(char *prompt, t_env *envp, bool env_i);
int		is_directory(const char *path);
void	exit_shell(t_minishell *minishell);

/*
ERRORS
*/

void	buffer_strlcat(char *dst, const char *src, size_t dstsize);
void	exit_error(t_minishell *minishell, const char *msg);
void	exit_errno(t_minishell *minishell, const char *msg, int mode);
void	error_lexer(t_minishell *msh, const char *error, bool quit);
void	print_error(t_minishell *minishell, const char *msg, bool quit);
void	print_errno(const char *error_command, int mode);
void	print_dot_error(const char *cmd_name);
void	builtin_usage(const char *command_name, const char *error);
int		builtin_error(const char *cmd, const char *arg, const char *er, int st);
int		invalid_id(const char *command_name, const char *variable_name);
int		invalid_option(const char *command_name, const char *option);
int		argument_error(const char *command_name);

/*
PARSER
*/

t_token	*malloc_token(t_minishell *mshl, const char *s, t_token_type tok_type);
void	delete_first_token(t_token *tokens);
void	delete_all_tokens(t_token **tokens);
t_lexer	*malloc_lexer(t_minishell *minishell);
void	reset_lexer(t_lexer *lexer, t_minishell *minishell);
void	free_lexer(t_lexer	*lexer);
int		split_into_tokens(t_minishell *msh, t_lexer *lexer);
void	print_lexer(t_lexer *lexer);
int		is_quote(char c);
char	*handle_quote(t_minishell *msh, char *word, t_lexer *lexer);
void	handle_metacharacter(t_minishell *msh, t_lexer *lexer);
char	*append_char_to_str(t_minishell *msh, char *str, char c);
void	add_token(t_minishell *minishell, char *s, int type);
t_cmd	*malloc_command(t_minishell *minishell);
void	free_command(t_cmd **cmd);
void	find_command(t_env *envp, t_cmd *cmd);
int		is_builtin(t_cmd *cmd);
char	*expand_relative_path(t_env *envp, char *cmd);
int		is_file(const char *name);
int		parse_tokens(t_minishell *minishell);
void	create_new_command(t_minishell *minishell, t_token *list);
void	unexpected_token(t_minishell *minishell, t_token *list);
bool	is_redir(t_token *token);
void	handle_redir(t_minishell *minishell, t_cmd *cmd, t_token *list);
int		create_heredoc(t_minishell *minishell, t_cmd *cmd, char *ending);
void	write_heredoc(t_minishell *msh, char *line, int fd, int mode);
void	warning_semi_backslash(t_lexer *lexer, char c);

#endif
