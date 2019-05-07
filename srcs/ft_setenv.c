/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_setenv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:23:01 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:23:03 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Create new environ array entry
** @param char *argv - arguments passed by user
** @return char * as new key value pair
*/

char	*env_entry(char **argv)
{
	char	*new_entry;
	int		size;

	if (argv[2] != NULL)
		size = ft_strlen(argv[1]) + ft_strlen(argv[2]) + 1 + 1;
	else
		size = ft_strlen(argv[1]) + 1 + 1;
	new_entry = (char *)malloc(sizeof(char) * size);
	new_entry[0] = '\0';
	ft_strcat(new_entry, argv[1]);
	ft_strcat(new_entry, "=");
	if (argv[2] != NULL)
		ft_strcat(new_entry, argv[2]);
	return (new_entry);
}

/*
** @desc Replace existing environment key's value
** @param char *argv - arguments passed by user
** @param int *xsetenv - indicates if environment list has been increased
** @param int *xunsetenv - indicates if environment list has been decreased
** @param t_setenv **h - head of individually edited environment variables list
** @return void
*/

void	environ_insert(char **argv, int *xsetenv, int *xunsetenv, t_setenv **h)
{
	int				i;
	char			*old_env;
	extern char		**environ;

	i = find_var(argv[1], 0);
	old_env = environ[i];
	environ[i] = env_entry(argv);
	if (*xsetenv != 0 || *xunsetenv != 0
	|| field_search(*h, argv[1]) == 1)
		free(old_env);
	if (*h == NULL)
		*h = new_field(argv[1]);
	else if (field_search(*h, argv[1]) == 0)
		append_field(*h, argv[1]);
}

/*
** @desc Create new environ array
** @param char *argv - arguments passed by user
** @return char ** as new environ list
*/

char	**environ_new(char **argv)
{
	int			count;
	char		**environ_new;
	extern char	**environ;

	count = 0;
	while (environ[count] != NULL)
		count++;
	environ_new = (char **)malloc(sizeof(char *) * (count + 1 + 1));
	count = 0;
	while (environ[count] != NULL)
	{
		environ_new[count] = ft_strdup(environ[count]);
		count++;
	}
	environ_new[count] = env_entry(argv);
	environ_new[count + 1] = NULL;
	return (environ_new);
}

/*
** @desc Inserts or resets environment variable
** @desc If environment variable doesn't exist, it is inserted with given value
** @desc If it does, key's value is replaced with given value or empty space
** @desc if no value is passed.
** @param char **argv - user input
** @param int *xsetenv - indicates if environment list has been increased
** @param int *xunsetenv - indicates if environment list has been decreased
** @param t_setenv **h - head of individually edited environment variables list
** @return void
*/

void	ft_setenv(char **argv, int *xsetenv, int *xunsetenv, t_setenv **h)
{
	extern char	**environ;
	char		**environ_cpy;
	char		***environ_ptr;

	environ_cpy = environ;
	environ_ptr = &environ;
	if (argv[1] == NULL)
		ft_putstr_fd("Please, enter environ variable\n", 2);
	else
	{
		if (find_var(argv[1], 0) == -1)
		{
			*environ_ptr = environ_new(argv);
			if (*xsetenv != 0 || *xunsetenv != 0)
				free_two_d(environ_cpy);
			(*xsetenv)++;
		}
		else
			environ_insert(argv, xsetenv, xunsetenv, h);
	}
}
