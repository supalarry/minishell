/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_variables.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:23:51 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:23:52 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Maintain linked list storing local shell variables
** @param t_shellvar **head_local - address of shell's local variables head
** @param char **line - address of input line from command line
** @return int 0 if erronous variable was passed in
** @return int 1 if correct variable was passed in
*/

int	shell_variables(t_shellvar **head_local, char **line)
{
	char	*val_start;
	char	**args;
	char	*line_cpy;

	args = ft_strsplit(*line, ' ');
	if (ft_strchr(args[0], '=') != NULL)
	{
		if (str_words(args) > 1)
		{
			launcher_error(args[1]);
			free_two_d(args);
			return (0);
		}
		line_cpy = ft_strdup(*line);
		val_start = ft_strchr(line_cpy, '=') + 1;
		*(val_start - 1) = '\0';
		if (*head_local == NULL)
			*head_local = new_var(line_cpy, val_start);
		else
			append_var(*head_local, line_cpy, val_start);
		free(line_cpy);
	}
	free_two_d(args);
	return (1);
}
