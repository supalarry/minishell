/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsetenv.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:23:07 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:23:09 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Create new environ array excluding specified key
** @param int target - index of key to be excluded
** @return char ** as new environ list without specified key
*/

static char	**cut_environ(int target)
{
	int			count;
	int			i;
	char		**environ_new;
	extern char	**environ;

	i = 0;
	count = 0;
	while (environ[count] != NULL)
		count++;
	environ_new = (char **)malloc(sizeof(char *) * (count));
	count = 0;
	while (environ[count] != NULL)
	{
		if (count != target)
		{
			environ_new[i] = ft_strdup(environ[count]);
			i++;
		}
		count++;
	}
	environ_new[count - 1] = NULL;
	return (environ_new);
}

/*
** @desc Removes user specified environment key if it's valid
** @param char *var - key to be deleted
** @param int *times_setenv - indicates if environment list has been increased
** @param int *times_unsetenv - indicates if environment list has been cut
** @return void
*/

static void	delete_env_var(char *var, int *times_setenv, int *times_unsetenv)
{
	int			i;
	extern char	**environ;
	char		**environ_cpy;
	char		***environ_ptr;

	i = find_var(var, 0);
	environ_cpy = environ;
	environ_ptr = &environ;
	if (i != -1)
	{
		*environ_ptr = cut_environ(i);
		if (*times_setenv != 0 || *times_unsetenv != 0)
			free_two_d(environ_cpy);
		(*times_unsetenv)++;
	}
	else
		ft_putstr_fd("Such environment variable does not exist\n", 2);
}

/*
** @desc Launched removal of user specified environment key
** @param char *args - user input from command line
** @param int *times_setenv - indicates if environment list has been increased
** @param int *times_unsetenv - indicates if environment list has been cut
** @return void
*/

void		ft_unsetenv(char **args, int *times_setenv, int *times_unsetenv)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
		ft_putstr_fd("Please, enter environ variable\n", 2);
	else if (args[2] != NULL)
		ft_putstr_fd("Please, specify only 1 environ variable\n", 2);
	else
		delete_env_var(args[1], times_setenv, times_unsetenv);
}
