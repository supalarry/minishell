/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   binary_launcher.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:21:28 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:21:41 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

pid_t	g_fork_ret;

/*
** @desc Launch corresponding binary within path
** @param char *path - absolute path to binary
** @param char **argv - arguments for executable
** @return void
*/

void	binary_launcher(char *path, char **argv)
{
	int			wait_ret;
	pid_t		child_pid;
	extern char	**environ;

	g_fork_ret = fork();
	if (g_fork_ret == 0)
	{
		execve(path, argv, environ);
	}
	else if (g_fork_ret > 0)
	{
		signal(SIGINT, child_handler);
		child_pid = wait(&wait_ret);
	}
}
