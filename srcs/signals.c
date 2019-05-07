/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:23:01 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:23:03 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Ignore signals from command line to minishell
** @param int signal - signal sent by keyboard
** @return void
*/

void	parent_handler(int signal)
{
	(void)signal;
}

/*
** @desc Send SIGINT signal to child process of minishell
** @desc after detecting Ctrl+C being pressed
** @param int signal - signal sent by keyboard
** @return void
*/

void	child_handler(int signal)
{
	if (signal == SIGINT)
		kill(g_fork_ret, SIGINT);
}
