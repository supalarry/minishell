/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:21:59 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:22:04 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Update environment variables PWD and OLDPWD
** @param char *old_pwd - path of old present working directory
** @param char *new_pwd - path of new present working directory
** @param t_setenv *head - linked list head with edited environment variables
** @return void
*/

static void	update_env_paths(char *old_pwd, char *new_pwd, t_setenv **head)
{
	char	*line_old;
	char	*line_new;
	char	*tmp_old;
	char	*tmp_new;

	tmp_old = ft_strdup("setenv OLDPWD ");
	tmp_new = ft_strdup("setenv PWD ");
	line_old = ft_strjoin(tmp_old, old_pwd);
	line_new = ft_strjoin(tmp_new, new_pwd);
	free(tmp_old);
	free(tmp_new);
	launcher(line_old, head, 0);
	launcher(line_new, head, 0);
	free(line_old);
	free(line_new);
}

/*
** @desc Return value of HOME variable if no directory is given
** @desc Return value of OLDPWD variable if '-' is given as directory
** @param char *line - user input from command line
** @param int i - integer storing start of directory
** @return char * as address of allocated string storing key's value
*/

static char	*cd_exception(char *line, int i)
{
	if (line[i] == '\0')
		return (dup_val("HOME"));
	else
		return (dup_val("OLDPWD"));
}

/*
** @desc Return index to start of destination directory
** @param char *line - user input from command line
** @return start index of destination directory
*/

static int	cd_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (line[i] == ' ')
		i++;
	return (i);
}

/*
** @desc Changes present working directory and updates environment variables
** @param char *line - user input containing path to change to
** @param t_setenv **head - address of variable containing names of
** @param environment variables that were edited for futher function later
** @return void
*/

void		cd(char *line, t_setenv **head)
{
	int		i;
	int		ret;
	char	old_pwd[4096];
	char	new_pwd[4096];

	i = cd_start(line);
	ret = 0;
	if (line[i] == '\0' || (line[i] != '\0' && line[i] == '-'))
	{
		line = cd_exception(line, i);
		getcwd(old_pwd, 4096);
		ret = chdir(line);
		getcwd(new_pwd, 4096);
		update_env_paths(old_pwd, new_pwd, head);
		free(line);
	}
	else if (line[i] != '\0' && line[i] != '-')
	{
		getcwd(old_pwd, 4096);
		ret = chdir(line + i);
		getcwd(new_pwd, 4096);
		update_env_paths(old_pwd, new_pwd, head);
	}
	if (ret == -1)
		cd_error(line + i);
}
