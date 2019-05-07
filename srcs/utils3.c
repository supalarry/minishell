/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:24:12 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:24:13 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Count number of specific characters within a string
** @param char *arg - argument passed in command line input
** @param char target - character to be counted in arg
** @return int as the count of target in arg
*/

int		char_count(char *arg, char target)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == target)
			count++;
		i++;
	}
	return (count);
}

/*
** @desc Step over '$' if necessary
** @param int dollar_expansion - 1 if '$' needs to be stepped over
** @param 0 if stepping over is not needed
** @param char **env_var - address of string where '$' is stepped over
** @return void
*/

void	step_over(char **env_var, int dollar_expansion)
{
	if (dollar_expansion == 1)
		*env_var = *env_var + 1;
}

/*
** @desc Detects equals sign for possible variable
** @param char *line - line from command input
** @return int 1 if '=' sign exists within line
** @return int 0 if '=' sign does not exist within line
*/

int		var_found(char *line)
{
	if (ft_strchr(line, '=') != NULL)
		return (1);
	return (0);
}
