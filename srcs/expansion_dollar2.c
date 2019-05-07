/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_dollar2.c                                 :+:    :+:           */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:22:25 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:22:28 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Combine two dimensional array into string with '/' in between
** @param char **args - two dimensional array to be merged
** @param char *arg - string containing '$'
** @return char * as merged line in which words are seperated by '/'
*/

static char	*str_combine_slash(char **args, char *arg)
{
	int		i;
	int		len;
	char	*combined;

	i = 0;
	len = 0;
	while (args[i] != NULL)
	{
		len = len + ft_strlen(args[i]);
		i++;
	}
	combined = (char *)malloc(sizeof(char) * len + i + 1);
	combined[0] = '\0';
	i = 0;
	ft_strcat(combined, "/");
	while (args[i] != NULL)
	{
		ft_strcat(combined, args[i]);
		if ((args[i + 1] != NULL
		&& combined[ft_strlen(combined) - 1] != '/')
		|| (args[i + 1] == NULL && arg[ft_strlen(arg) - 1] == '/'))
			ft_strcat(combined, "/");
		i++;
	}
	return (combined);
}

/*
** @desc Expand '$' variables if path is given
** @param char *arg - string containing a path with '$' somewhere
** @param char **arg_ptr - address of arg
** @param t_shellvar *head_local - head of linked list with local variables
** @return void
*/

void		dollar_dir(char *arg, char **arg_ptr, t_shellvar *head_local)
{
	int			j;
	char		**dir;
	char		*arg_cpy;
	extern char	**environ;

	j = 0;
	dir = ft_strsplit(arg, '/');
	arg_cpy = arg;
	while (dir[j] != NULL)
	{
		if (char_count(dir[j], '$') > 1 || dir[j][0] != '$')
			multiple_dollars(&dir[j], environ, head_local);
		else
			one_dollar(&dir[j], environ, head_local);
		j++;
	}
	*arg_ptr = str_combine_slash(dir, arg);
	free(arg_cpy);
	free_two_d(dir);
}
