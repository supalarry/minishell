/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_dollar.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:22:25 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:22:28 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Replace $ with environment variable
** @param char **arg - address of not expanded argument from standard input
** @param char *environ - two dimensional array storing environment variables
** @param int single_dollar - indicates if this function is used by
** @param single_dollars() with value of 1 or multiple_dollars with value of 0.
** @param 1 is used to step over '$' sign when splitting input line by ' '
** @param 0 is does not require it as argument is split by '$' already
** @return void
*/

void	dollar_env(char **arg, char **environ, int single_dollar)
{
	int		expanded_len;
	char	*expanded;
	char	*old_arg;
	int		val_start;
	int		i;

	expanded_len = key_val_len(*arg, single_dollar);
	expanded = (char *)malloc(sizeof(char) * expanded_len + 1);
	expanded[0] = '\0';
	old_arg = *arg;
	val_start = key_val_start(*arg, single_dollar);
	i = find_var(*arg, single_dollar);
	ft_strcat(expanded, environ[i] + val_start);
	*arg = expanded;
	free(old_arg);
}

/*
** @desc Replace $ with locally defined shell variable or empty string
** @param char **arg - address of not expanded argument from standard input
** @param t_shellvar *head_local - head of linked list storing local variables
** @param int single_dollar - indicates if this function is used by
** @param single_dollars() with value of 1 or multiple_dollars with value of 0.
** @return void
*/

void	dollar_local(char **arg, t_shellvar *head_local, int single_dollar)
{
	int		expanded_len;
	char	*expanded;
	char	*old_arg;
	int		found;

	old_arg = *arg;
	found = var_search(head_local, *arg + single_dollar);
	if (found == 1)
	{
		expanded_len = var_len(head_local, *arg);
		expanded = (char *)malloc(sizeof(char) * expanded_len + 1);
		expanded[0] = '\0';
		ft_strcat(expanded, var_value(head_local, *arg + single_dollar));
	}
	else
	{
		expanded = (char *)malloc(sizeof(char) * 1);
		expanded[0] = '\0';
	}
	*arg = expanded;
	free(old_arg);
}

/*
** @desc If $HOME$USER is given, split this string into individual parts
** @desc to expand each and then combine back into one, or if text
** @desc before as in 'word$HOME' exists split string by '$' delimeter
** @param char **arg - address of not expanded argument from standard input
** @param with multiple '$' signs
** @param char **environ - address of array containing environment variables
** @param t_shellvar *head_local - head of linked list storing local variables
** @return void
*/

void	multiple_dollars(char **arg, char **environ, t_shellvar *head)
{
	int		i;
	char	**dollars;

	i = 0;
	dollars = ft_strsplit(*arg, '$');
	while (dollars[i] != NULL)
	{
		if (find_var(dollars[i], 0) != -1)
			dollar_env(&dollars[i], environ, 0);
		else if (var_search(head, dollars[i]) == 1)
			dollar_local(&dollars[i], head, 0);
		i++;
	}
	free(*arg);
	*arg = str_combine(dollars, 0);
	free_two_d(dollars);
}

/*
** @desc Expand argument if it only contains of one variable to expand
** @param char **arg - address of not expanded argument from standard input
** @param with one '$' signs and nothing before '$' sign
** @param char **environ - address of array containing environment variables
** @param t_shellvar *head - head of linked list storing local variables
** @return void
*/

void	one_dollar(char **arg, char **environ, t_shellvar *head)
{
	if (find_var((*arg), 1) != -1)
		dollar_env(arg, environ, 1);
	else
		dollar_local(arg, head, 1);
}

/*
** @desc Replace $ with environment or shell's locally defined variables
** @param char **line - address of not expanded line from standard input
** @param char **args - two dimensional array where each item is word from line
** @param including $ sign to see which items need expansion
** @param t_shellvar *head_local - head of linked list storing local variables
** @return void
*/

void	dollar(char **line, char **args, t_shellvar *head_local)
{
	int			i;
	extern char	**environ;
	char		*line_cpy;

	i = 0;
	line_cpy = *line;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '$') != NULL && ft_strlen(args[i]) > 1)
		{
			if (ft_strchr(args[i], '/'))
				dollar_dir(args[i], &args[i], head_local);
			else
			{
				if (char_count(args[i], '$') > 1 || args[i][0] != '$')
					multiple_dollars(&args[i], environ, head_local);
				else
					one_dollar(&args[i], environ, head_local);
			}
		}
		i++;
	}
	free(line_cpy);
	*line = str_combine(args, 1);
}
