/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:24:12 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:24:13 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Combine two dimensional array into one string with spaces
** @param char **args - two dimensional array to be merged
** @param int spaces - 1 if seperation by spaces is needed. 0 otherwise.
** @return char * as merged line in which words are seperated by spaces
*/

char	*str_combine(char **args, int spaces)
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
	while (args[i] != NULL)
	{
		ft_strcat(combined, args[i]);
		if (args[i + 1] != NULL && spaces == 1
		&& combined[ft_strlen(combined) - 1] != ' ')
			ft_strcat(combined, " ");
		i++;
	}
	return (combined);
}

/*
** @desc Count words withing two dimensional array
** @param char **args - two dimensional array to be counted
** @return int as words within two dimensional array
*/

int		str_words(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

/*
** @desc Count total lengths of all words withing two dimensional array
** @param char **args - two dimensional array with words to be counted
** @return int as characters within two dimensional array
*/

int		str_chars(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i] != NULL)
	{
		count = count + ft_strlen(args[i]);
		i++;
	}
	return (count);
}

/*
** @desc Check if input is not empty
** @param char *line - user input line
** @return int 1 if any input was given
** @return int 0 if empty line was given
*/

int		input_exists(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] > 32 && line[i] <= 126)
			return (1);
		i++;
	}
	return (0);
}

/*
** @desc Given absolute path, check if file exists or does not exist
** @param char *absolute_path - binary/file within specific folder
** @return int 0 if binary/file exists in particular folder
** @return int -1 if binary/file does not exist in particular folder
*/

int		binary_access(char *absolute_path)
{
	return (access(absolute_path, F_OK));
}
