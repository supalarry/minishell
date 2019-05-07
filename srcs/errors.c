/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:22:50 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:22:52 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Display error if invalid command was passed to shell
** @param char *command - faulty command
** @return void
*/

void	launcher_error(char *command)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\n", 2);
}

/*
** @desc Display error if invalid directory was passed in cd
** @param char *directory - invalid directory
** @return void
*/

void	cd_error(char *directory)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putstr_fd(directory, 2);
	ft_putstr_fd("\n", 2);
}

/*
** @desc Display error if invalid user was passed in to ~ expansion
** @param char *user - invalid user
** @return void
*/

void	display_user_error(char *user)
{
	ft_putstr_fd("minishell: no such user or named directory: ", 2);
	ft_putstr_fd(user, 2);
	ft_putstr_fd("\n", 2);
}

/*
** @desc Determine if a user exists
** @param char *user - user to be validated
** @return void
*/

int		user_error(char *user)
{
	int		access_ret;
	int		expanded_len;
	char	*expanded;

	if (user[0] == '~' && ft_isalpha(user[1]))
	{
		expanded_len = ft_strlen(user) + ft_strlen("/Users/");
		expanded = (char *)malloc(sizeof(char) * expanded_len);
		expanded[0] = '\0';
		ft_strcat(expanded, "/Users/");
		ft_strcat(expanded, user + 1);
		access_ret = binary_access(expanded);
		free(expanded);
		if (access_ret == -1)
			return (1);
	}
	return (0);
}

/*
** @desc Determine if errors exist before interpreting and launching commands
** @param char **line - address of input line to be validated
** @return int 1 if user input has an error
** @return int 0 if user input has no error
*/

int		error_detected(char **line)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_strsplit(*line, ' ');
	while (args[i] != NULL)
	{
		if (user_error(args[i]) == 1)
		{
			display_user_error(args[i] + 1);
			free_two_d(args);
			free(*line);
			return (1);
		}
		i++;
	}
	free_two_d(args);
	return (0);
}
