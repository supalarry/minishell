/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_builtin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:23:20 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:23:22 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Determine if command given is built in shell command
** @param char *command - name of command
** @return int 1 if command is built in shell
** @return int 0 if command is not built in shell
*/

int		is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0
	|| ft_strcmp(command, "cd") == 0
	|| ft_strcmp(command, "setenv") == 0
	|| ft_strcmp(command, "unsetenv") == 0
	|| ft_strcmp(command, "env") == 0
	|| ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}
