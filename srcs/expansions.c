/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:22:50 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:22:52 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Checks if arguments passed to program needs expansion
** @desc and determines which expansion/s exactly.
** @param char **line - address of not expanded line from standard input
** @param t_shellvar *head_local - head of shell's local variables linked list
** @return void
*/

void	expansions(char **line, t_shellvar *head_local)
{
	char	**args;

	args = ft_strsplit(*line, ' ');
	if (is_tilde(args) > 0)
		tilde(line, args);
	free_two_d(args);
	args = ft_strsplit(*line, ' ');
	if (ft_strchr(*line, '$'))
		dollar(line, args, head_local);
	free_two_d(args);
}

/*
** @desc Determine if tilde expansion is necessary
** @param char **args - user input as an array
** @return void
*/

int		is_tilde(char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if ((args[i][0] == '~' && (args[i][1] == '\0' || args[i][1] == '/'))
		|| (args[i][0] == '~' && args[i][1] == '+'
		&& (args[i][2] == '\0' || args[i][2] == '/'))
		|| (args[i][0] == '~' && args[i][1] == '-' &&
		(args[i][2] == '\0' || args[i][2] == '/'))
		|| (args[i][0] == '~' && ft_isalpha(args[i][1])))
			return (1);
		i++;
	}
	return (0);
}
