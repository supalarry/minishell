/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:24:06 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:24:08 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Extracts key even with '=' in key name
** @param char *var - variable from which to extract key
** @return char * as key extracted from variable
*/

char	*extract_key(char *var)
{
	int		len;
	char	*key;

	len = ft_strlen(var);
	key = ft_strdup(var);
	while (key[len] != '=')
		len--;
	key[len] = '\0';
	return (key);
}

/*
** @desc Finds key passed as argument in environment key's
** @param char *env_var - target key
** @param int dollar_expansion - determines whether to step over '$' sign
** @return int i as index of key in environ list
** @return int -1 if key does not exist in environ list
*/

int		find_var(char *env_var, int dollar_expansion)
{
	int			i;
	char		*key;
	extern char	**environ;

	i = 0;
	step_over(&env_var, dollar_expansion);
	while (environ[i] != NULL)
	{
		if (ft_strstr(environ[i], env_var) != NULL)
		{
			key = extract_key(environ[i]);
			if (ft_strcmp(key, env_var) == 0)
			{
				free(key);
				break ;
			}
			free(key);
		}
		i++;
	}
	if (environ[i] == NULL)
		return (-1);
	return (i);
}

/*
** @desc Finds which letter in environ key is first letter of value
** @param char *key - key which value is searched e.g. HOME or PWD
** @param int dollar_expansion - determines whether to step over '$' sign
** @return int to indicate start of the value in key value pair string
*/

int		key_val_start(char *key, int dollar_expansion)
{
	int			i;
	int			j;
	extern char **environ;

	if (dollar_expansion == 1)
		key++;
	i = find_var(key, 0);
	j = 0;
	while (environ[i][j] != '=' && environ[i][j] != '\0')
		j++;
	if (environ[i][j] != '\0')
		j++;
	return (j);
}

/*
** @desc Finds length of a value in key value pair of environ
** @param char *key - key which length is searched e.g. HOME or PWD
** @param int dollar_expansion - determines whether to step over '$' sign
** @return int to indicate length of the value in key value pair string
*/

int		key_val_len(char *key, int dollar_expansion)
{
	int			i;
	int			j;
	int			len;
	extern char	**environ;

	if (dollar_expansion == 1)
		key++;
	i = find_var(key, 0);
	j = 0;
	len = 0;
	while (environ[i][j] != '=' && environ[i][j] != '\0')
		j++;
	j++;
	while (environ[i][j] != '\0')
	{
		j++;
		len++;
	}
	return (len);
}

/*
** @desc Duplicates value of a key
** @param char *key - key which value is duplicated e.g. HOME or PWD
** @return char * as duplicated value of the key
*/

char	*dup_val(char *key)
{
	int			i;
	int			len;
	int			start;
	char		*val;
	extern char	**environ;

	i = find_var(key, 0);
	len = key_val_len(key, 0);
	start = key_val_start(key, 0);
	val = (char *)malloc(sizeof(char) * len + 1);
	val[0] = '\0';
	ft_strcat(val, environ[i] + start);
	return (val);
}
