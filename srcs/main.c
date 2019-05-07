/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:23:26 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:23:28 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Launch builtin or binary launcher
** @param char *line - already expanded line from standard input
** @param t_setenv *head - address of head of linked list with
** @param environment variables
** @param int var - 0 if variable was not set in user input
** @param int var - 1 if variable was set in user input
** @return void
*/

void	launcher(char *line, t_setenv **head, int var)
{
	char	**args;
	char	*path;

	if (ft_strlen(line) == 0)
		return ;
	args = ft_strsplit(line, ' ');
	path = is_binary(args[0]);
	if (is_builtin(args[0]))
		builtin_launcher(line, args, head);
	else if (path != NULL)
		binary_launcher(path, args);
	else if (var == 0)
		launcher_error(args[0]);
	if (path != NULL && line[0] != '/')
		free(path);
	free_two_d(args);
}

/*
** @desc Replicate shell by executing binaries and bult in commands
** @desc and control and get information about environment
** @param void
** @return int 0 if program ran successfully
*/

int		main(void)
{
	char				*line;
	static t_setenv		*head;
	static t_shellvar	*head_local;

	signal(SIGINT, parent_handler);
	while (ft_strncmp("exit", line, 4) != 0)
	{
		get_next_line(0, &line);
		remove_spacing(&line);
		if (error_detected(&line) == 1)
			continue;
		if (input_exists(line))
		{
			if (shell_variables(&head_local, &line) == 1)
			{
				expansions(&line, head_local);
				launcher(line, &head, var_found(line));
			}
		}
		if (ft_strncmp("exit", line, 4) != 0)
			free(line);
	}
	free(line);
	free_lists(head, head_local);
	return (0);
}
