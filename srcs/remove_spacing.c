/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_spacing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 13:28:52 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:23:37 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Launches functions to remove redundant spacing in start, end, middle
** @param char **line - address of pointer storing user input
** @return void
*/

void	remove_spacing(char **line)
{
	char		*line_cpy;

	line_cpy = *line;
	*line = ft_strtrim(*line);
	free(line_cpy);
	line_cpy = *line;
	*line = remove_seperating_spaces(*line);
	free(line_cpy);
}

/*
** @desc Determine correct amount of characters without double spaces/tabs
** @param char *line - line from command line as user input
** @return int as characters in string excluding multiple spacing between words
*/

int		single_spacing_len(char *line)
{
	int		i;
	int		state;
	int		state_quote;
	int		len;

	i = 0;
	len = 0;
	state = 1;
	state_quote = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '\"') && state_quote != 1)
			state_quote = 1;
		else if ((line[i] == '\'' || line[i] == '\"') && state_quote == 1)
			state_quote = 0;
		if ((line[i] > 32 && line[i] <= 126) || state == 1 || state_quote == 1)
		{
			len++;
			state = 1;
		}
		if (!(line[i] > 32 && line[i] <= 126) && state == 1 && state_quote != 1)
			state = 0;
		i++;
	}
	return (i);
}

/*
** @desc Remove spaces between words of a string
** @param char *line - string in which spaces between words must be removed
** @return char * as a string with removed spaces in between
*/

char	*remove_seperating_spaces(char *line)
{
	int		i;
	int		j;
	int		state;
	int		state_quote;
	char	*trimmed;

	i = 0;
	j = 0;
	trimmed = (char *)malloc(sizeof(char) * single_spacing_len(line) + 1);
	state = 1;
	state_quote = 0;
	while (line[i] != '\0')
	{
		set_state_quote(line[i], &state_quote);
		if ((line[i] > 32 && line[i] <= 126) || state == 1 || state_quote == 1)
		{
			trimmed[j] = ((line[i] > 32 && line[i] <= 126) ? line[i] : ' ');
			j++;
			state = 1;
		}
		reset_state(line[i], &state, &state_quote);
		i++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}

/*
** @desc Decide if current position in input line is between ' or " or outside
** @param char item - current character from the input line
** @param int *state_quote - pointer to int telling if position is in quotes
** @return void
*/

void	set_state_quote(char item, int *state_quote)
{
	if ((item == '\'' || item == '\"') && *state_quote != 1)
		*state_quote = 1;
	else if ((item == '\'' || item == '\"') && *state_quote == 1)
		*state_quote = 0;
}

/*
** @desc Decide if state variable needs to be reset
** @param char item - current character from the input line
** @param int *state - pointer to int telling if double space was encountered
** @param int *state_quote - pointer to int telling if position is in quotes
** @return void
*/

void	reset_state(char item, int *state, int *state_quote)
{
	if (!(item > 32 && item <= 126) && *state == 1 && *state_quote != 1)
		*state = 0;
}
