/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_tilde.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:22:40 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:22:44 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Carry expansion for ~user to expand to home directory of user
** @param char **arg - address of not expanded argument from standard input
** @return void, but store new argument in old ones place at the same address
*/

void	tilde_usr(char **arg)
{
	int		expanded_len;
	char	*expanded;
	char	*old_arg;

	expanded_len = ft_strlen(*arg) + ft_strlen("/Users/");
	expanded = (char *)malloc(sizeof(char) * expanded_len);
	expanded[0] = '\0';
	old_arg = *arg;
	ft_strcat(expanded, "/Users/");
	ft_strcat(expanded, *arg + 1);
	*arg = expanded;
	free(old_arg);
}

/*
** @desc Carry expansion for ~, ~+ and ~-
** @param char **arg - address of not expanded argument from standard input
** @param char *target - variable from environ which value needs to be appended
** @param char *environ - two dimensional array storing environment variables
** @return void, but store new argument in old ones place at the same address
*/

void	tilde_dir(char **arg, char *target, char **environ)
{
	int		expanded_len;
	char	*expanded;
	char	*old_arg;
	int		val_start;
	int		i;

	expanded_len = ft_strlen(*arg) + key_val_len(target, 0);
	expanded = (char *)malloc(sizeof(char) * expanded_len);
	expanded[0] = '\0';
	old_arg = *arg;
	val_start = key_val_start(target, 0);
	i = find_var(target, 0);
	ft_strcat(expanded, environ[i] + val_start);
	if (ft_strcmp(target, "HOME") == 0)
		ft_strcat(expanded, *arg + 1);
	else
		ft_strcat(expanded, *arg + 2);
	*arg = expanded;
	free(old_arg);
}

/*
** @desc Determine which tilde expansion is needed
** @param char *arg - individual argument between arguments from standard input
** @return 1 if ~ expansion is needed for home folder of current user
** @return 2 if ~+ expansion is needed for present working directory
** @return 3 if ~- expansion is needed for old present working directory
** @return 3 if ~user expansion is needed for home folder of specific user
*/

int		tilde_type(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '~' && (arg[i + 1] == '\0' || arg[i + 1] == '/'))
		return (1);
	else if (arg[i] == '~' && arg[i + 1] == '+' &&
	(arg[i + 2] == '\0' || arg[i + 2] == '/'))
		return (2);
	else if (arg[i] == '~' && arg[i + 1] == '-' &&
	(arg[i + 2] == '\0' || arg[i + 2] == '/'))
		return (3);
	else if (arg[i] == '~' && ft_isalpha(arg[i + 1]))
		return (4);
	return (0);
}

/*
** @desc Launch functions for (~, ~+, ~-) or ~user expansions
** @param char **line - address of not expanded line from standard input
** @param char **args - two dimensional array where each item is word from line
** @return void
*/

void	tilde(char **line, char **args)
{
	int			type;
	int			i;
	char		*line_cpy;
	extern char	**environ;

	type = 0;
	i = 1;
	line_cpy = *line;
	while (args[i] != NULL)
	{
		type = tilde_type(args[i]);
		if (type == 1)
			tilde_dir(&args[i], "HOME", environ);
		else if (type == 2)
			tilde_dir(&args[i], "PWD", environ);
		else if (type == 3)
			tilde_dir(&args[i], "OLDPWD", environ);
		else if (type == 4)
			tilde_usr(&args[i]);
		i++;
	}
	free(line_cpy);
	*line = str_combine(args, 1);
}
