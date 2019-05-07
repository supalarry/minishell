/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_header.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:21:59 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:22:04 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_HEADER_H
# define MINISHELL_HEADER_H
# include <signal.h>
# include "../libft/includes/libft.h"

extern pid_t			g_fork_ret;
typedef	struct			s_setenv
{
	char				*name;
	struct s_setenv		*next;
}						t_setenv;

typedef	struct			s_shellvar
{
	char				*name;
	char				*value;
	struct s_shellvar	*next;
}						t_shellvar;

int						binary_access(char *absolute_path);
char					**path_extract(char *path);
char					*path_finder(void);
char					*absolute_path_generate(char *binary, char *directory);
void					free_two_d(char **two_d);
char					*is_binary(char *binary);
void					launcher(char *line, t_setenv **head, int var);
void					binary_launcher(char *path, char **argv);
int						is_builtin(char *command);
void					builtin_launcher(char *line, char **args,
						t_setenv **head);
void					echo(char *line);
void					cd(char *line, t_setenv **head);
void					env(void);
void					ft_unsetenv(char **args, int *times_setenv,
						int *times_unsetenv);
void					ft_setenv(char **argv, int *times_setenv,
						int *times_unsetenv, t_setenv **head);
t_setenv				*new_field(char *field);
void					append_field(t_setenv *head, char *field);
int						field_search(t_setenv *head, char *field);
void					free_setenv_link(t_setenv *head);
void					expansions(char **line, t_shellvar *head_local);
void					tilde(char **line, char **args);
int						is_tilde(char **args);
char					*str_combine(char **args, int spaces);
int						key_val_start(char *key, int dollar_expansion);
int						key_val_len(char *key, int dollar_expansion);
int						find_var(char *env_var, int dollar_expansion);
void					tilde_usr(char **arg);
void					tilde_dir(char **arg, char *target, char **environ);
int						tilde_type(char *arg);
int						str_words(char **args);
int						shell_variables(t_shellvar **head_local, char **line);
t_shellvar				*new_var(char *variable, char *value);
void					append_var(t_shellvar *head, char *variable,
						char *value);
int						var_search(t_shellvar *head, char *variable);
void					free_var_link(t_shellvar *head);
int						var_len(t_shellvar *head, char *variable);
char					*var_value(t_shellvar *head, char *variable);
void					dollar(char **line, char **args,
						t_shellvar *head_local);
void					ft_putstr_no_quotes(char const *s);
char					*dup_val(char *key);
int						input_exists(char *line);
char					*remove_seperating_spaces(char *line);
void					remove_spacing(char **line);
int						single_spacing_len(char *line);
void					parent_handler(int signal);
void					child_handler(int signal);
void					launcher_error(char *command);
void					cd_error(char *directory);
void					display_user_error(char *user);
void					free_lists(t_setenv *head, t_shellvar *head_local);
int						error_detected(char **line);
int						user_error(char *user);
char					*determine_path(char *binary, char **bin_locations,
						int i);
char					*env_entry(char **argv);
void					environ_insert(char **argv, int *xsetenv,
						int *xunsetenv, t_setenv **h);
char					**environ_new(char **argv);
void					ft_setenv(char **argv, int *xsetenv, int *xunsetenv,
						t_setenv **h);
void					dollar_env(char **arg, char **environ,
						int single_dollar);
void					dollar_local(char **arg, t_shellvar *head_local,
						int single_dollar);
void					multiple_dollars(char **arg, char **environ,
						t_shellvar *head);
void					one_dollar(char **arg, char **environ,
						t_shellvar *head);
int						str_chars(char **args);
int						char_count(char *arg, char target);
void					dollar_dir(char *arg, char **arg_ptr,
						t_shellvar *head_local);
void					step_over(char **env_var, int dollar_expansion);
void					set_state_quote(char item, int *state_quote);
void					reset_state(char item, int *state, int *state_quote);
int						var_found(char *line);
#endif
