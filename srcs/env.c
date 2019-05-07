/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:22:16 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:22:18 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Output environment variables
** @param void
** @return void
*/

void	env(void)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i] != NULL)
	{
		ft_putstr(environ[i]);
		ft_putchar('\n');
		i++;
	}
}
