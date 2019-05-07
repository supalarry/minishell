/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setenv_linked.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:23:44 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:23:45 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Originate new node for individually edited environment variable
** @param char *field - name of environment variable that was edited
** @return t_setenv * as address of node storing variable's name
*/

t_setenv	*new_field(char *field)
{
	t_setenv	*new_node;

	new_node = (t_setenv*)malloc(sizeof(t_setenv));
	new_node->name = ft_strdup(field);
	new_node->next = NULL;
	return (new_node);
}

/*
** @desc Append new node for individually edited environment variable
** @param t_setenv *head - address of edited environment variables list
** @param char *field - name of environment variable that was edited
** @return void
*/

void		append_field(t_setenv *head, char *field)
{
	while (head->next != NULL)
		head = head->next;
	head->next = new_field(field);
}

/*
** @desc Search for specific variable within linked list of edited variables
** @param t_setenv *head - address of edited environment variables list
** @param char *field - name of environment variable to search for
** @return 1 if variable exists in linked list
** @return 0 if variable does not exist in linked list
*/

int			field_search(t_setenv *head, char *field)
{
	while (head != NULL)
	{
		if (ft_strcmp(head->name, field) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}
