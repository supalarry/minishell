/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_binary.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 14:23:13 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/04/30 14:23:14 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

/*
** @desc Determine if binary exists in one of path folders
** @param char *binary - name of the binary
** @return char * as absolute path to binary if it exists in one of path folders
** @return NULL if binary does not exist in one of path folders
*/

char	*is_binary(char *binary)
{
	int		i;
	char	*path;
	char	**bin_locations;
	char	*absolute_path;

	i = 0;
	path = path_finder();
	if (path != NULL)
	{
		bin_locations = path_extract(path);
		while (bin_locations[i] != NULL)
		{
			absolute_path = determine_path(binary, bin_locations, i);
			if (binary_access(absolute_path) == 0)
			{
				free_two_d(bin_locations);
				return (absolute_path);
			}
			if (binary[0] != '/')
				free(absolute_path);
			i++;
		}
		free_two_d(bin_locations);
	}
	return (NULL);
}

/*
** @desc Determine if path list exists in environ array
** @param void
** @return char * containing string with path variable
** @return NULL if path variable does not exist in environ
*/

char	*path_finder(void)
{
	int			i;
	int			found;
	extern char	**environ;

	i = 0;
	found = 0;
	while (environ[i] != NULL && found != 1)
	{
		if (ft_strstr(environ[i], "PATH=") != NULL)
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found == 1)
		return (environ[i]);
	return (NULL);
}

/*
** @desc Given path string, extract individual paths
** @param char *path - string containing all paths containing executables
** @return char ** containing individual directories as strings
** @return NULL if path is invalid
*/

char	**path_extract(char *path)
{
	char	**bin_locations;

	if (path == NULL)
		return (NULL);
	path = path + 5;
	bin_locations = ft_strsplit(path, ':');
	return (bin_locations);
}

/*
** @desc Determine if absolute path is already given to the binary
** @param char *binary - name or full path to the binary
** @param char **bin_locations - binary locations from $PATH
** @param int i - idex of a specific location from $PATH
** @return char *binary if absolute path is given already
** @return absolute_path_generate() result if absolute path is not given
*/

char	*determine_path(char *binary, char **bin_locations, int i)
{
	if (binary[0] == '/')
		return (binary);
	else
		return (absolute_path_generate(binary, bin_locations[i]));
}

/*
** @desc Create absolute path given directory and file
** @param char *binary - name of the binary
** @param char *directory - directory path from PATH
** @return char * as absolute path to the file
*/

char	*absolute_path_generate(char *binary, char *directory)
{
	char	*enter_folder;
	char	*absolute_path;

	enter_folder = ft_strjoin(directory, "/");
	absolute_path = ft_strjoin(enter_folder, binary);
	free(enter_folder);
	return (absolute_path);
}
