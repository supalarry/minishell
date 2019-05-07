/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_vars_linked.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:23:59 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:24:00 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Originate new node for locally defined shell variable
** @param char *variable - name of variable
** @param char *value - value of variable
** @return t_shellvar * as address of node storing variable
*/

t_shellvar	*new_var(char *variable, char *value)
{
	t_shellvar	*new_node;

	new_node = (t_shellvar*)malloc(sizeof(t_shellvar));
	new_node->name = ft_strdup(variable);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

/*
** @desc Append new node for locally defined shell variable
** @param t_shellvar *head - address of locally defined variables list
** @param char *variable - name of variable
** @param char *value - value of variable
** @return void
*/

void		append_var(t_shellvar *head, char *variable, char *value)
{
	while (head->next != NULL)
		head = head->next;
	head->next = new_var(variable, value);
}

/*
** @desc Search for specific variable within linked list of local variables
** @param t_shellvar *head - address of locally defined variables list
** @param char *variable - name of variable to search for
** @return 1 if variable exists in linked list
** @return 0 if variable does not exist in linked list
*/

int			var_search(t_shellvar *head, char *variable)
{
	while (head != NULL)
	{
		if (ft_strcmp(head->name, variable) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

/*
** @desc Define length of locally defined variable's value
** @param t_shellvar *head - address of locally defined variables list
** @param char *variable - name of variable to search for
** @return int as length of value if variable exists in linked list
** @return 0 if variable does not exist in linked list
*/

int			var_len(t_shellvar *head, char *variable)
{
	while (head != NULL)
	{
		if (ft_strcmp(head->name, variable) == 0)
			return (ft_strlen(head->value));
		head = head->next;
	}
	return (0);
}

/*
** @desc Search for specific variable's value within linked list
** @param t_shellvar *head - address of locally defined variables list
** @param char *variable - name of variable to search for
** @return char * as address of variable's value
** @return NULL if variable does not exist in linked list
*/

char		*var_value(t_shellvar *head, char *variable)
{
	while (head != NULL)
	{
		if (ft_strcmp(head->name, variable) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}
