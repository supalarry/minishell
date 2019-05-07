/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_launcher.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:21:49 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:21:53 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Launch appropriate builtin function
** @param char *line - user's input in command line
** @param char **args - user's input as two dimensional array
** @param t_setenv **head - address of edited environment variables list head
** @return void
*/

void	builtin_launcher(char *line, char **args, t_setenv **head)
{
	static int	times_setenv;
	static int	times_unsetenv;

	if (ft_strcmp(args[0], "echo") == 0)
		echo(line);
	else if (ft_strcmp(args[0], "cd") == 0)
		cd(line, head);
	else if (ft_strcmp(args[0], "env") == 0)
		env();
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		ft_unsetenv(args, &times_setenv, &times_unsetenv);
	else if (ft_strcmp(args[0], "setenv") == 0)
		ft_setenv(args, &times_setenv, &times_unsetenv, head);
}
