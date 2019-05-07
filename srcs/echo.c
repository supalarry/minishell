/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:22:10 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:22:13 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Output user input
** @param char *line - user input to be printed
** @return void
*/

void	echo(char *line)
{
	int	i;

	i = 0;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (line[i] == ' ')
		i++;
	if (line[i] != '\0')
		ft_putstr_no_quotes(&line[i]);
	ft_putstr("\n");
}

/*
** @desc Output string without ' and " quotes
** @param char const *s - string to be printed
** @return void
*/

void	ft_putstr_no_quotes(char const *s)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			if (s[i] != '\'' && s[i] != '\"')
				write(1, &s[i], 1);
			i++;
		}
	}
}
