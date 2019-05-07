/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:22:56 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:22:58 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Given two dimensional array, free its arrays and pointer itself
** @param char **two_d - two dimensional array
** @return void
*/

void	free_two_d(char **two_d)
{
	int		i;

	i = 0;
	while (two_d[i] != NULL)
	{
		free(two_d[i]);
		i++;
	}
	if (two_d != NULL)
		free(two_d);
}

/*
** @desc Launches functions to free environment and local variables
** @param t_setenv *head - head of linked list with environment variables
** @param t_shellvar *head_local - head of linked list with local variables
** @return void
*/

void	free_lists(t_setenv *head, t_shellvar *head_local)
{
	free_setenv_link(head);
	free_var_link(head_local);
}

/*
** @desc Free information about individually edited environment variables
** @param t_setenv *head - head of linked list
** @return void
*/

void	free_setenv_link(t_setenv *head)
{
	t_setenv	*temp;

	while (head != NULL)
	{
		free(head->name);
		temp = head;
		head = head->next;
		free(temp);
	}
}

/*
** @desc Free information about local shell variables
** @param t_shellvar *head - head of linked list
** @return void
*/

void	free_var_link(t_shellvar *head)
{
	t_shellvar	*temp;

	while (head != NULL)
	{
		free(head->name);
		free(head->value);
		temp = head;
		head = head->next;
		free(temp);
	}
}
