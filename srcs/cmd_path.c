/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:48:05 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/05 16:46:55 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_path(char **env)
{
	size_t	size;
	int		index_path;

	size = 5;
	index_path = 0;
	while (env[index_path])
	{
		if (ft_strncmp("PATH=\n", env[index_path], size) == 0)
			break ;
		index_path++;
	}
	return (index_path);
}

/* char	*check_path(char **av, int cmd, char **array_path, t_pipex pipex)
{
	char	**array_cmd;
	char	*path;

	if ((av[cmd + 2][0] == '/' && ft_strlen(av[cmd + 2]) == 1)
		|| (av[cmd + 2][0] == '/' && av[cmd + 2][1] == '.'))
	{
		free_str(array_path);
		cmd_notfound(pipex);
	}
	if ((av[cmd + 2][0] == '.' && av[cmd + 2][1] == '/')
		&& ft_strlen(av[cmd + 2]) == 2)
	{
		free_str(array_path);
		cmd_notfound(pipex);
	}
	else
	{
		array_cmd = ft_split(av[cmd + 2], ' ');
		path = ft_strdup(array_cmd[0]);
		free_str(array_path);
		free_str(array_cmd);
		return (path);
	}
	return (NULL);
}
 */
char	*boucle_path(char **array_path, char **array_cmd)
{
	char	*path;
	int index_path;

	index_path = 0;
	while (array_path[index_path])
	{
		path = ft_strcat2(array_path[index_path], array_cmd[0]);
		if (!path)
			break ;
		if (access(path, F_OK) == 0)
		{
			free_str(array_cmd);
			return (path);
		}
		free(path);
		index_path++;
	}
	free_str(array_cmd);
	return (NULL);
}
char	*ft_strcat2(char *dest, char *src)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!src || !dest)
		return (NULL);
	tmp = malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(src)) + 2);
	while (dest[i])
	{
		tmp[i] = dest[i];
		i++;
	}
	tmp[i++] = '/';
	while (src[j])
	{
		tmp[i] = src[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

/* char	*get_path(char **av, char **env, int cmd, t_pipex pipex)
{
	char		*path;
	int			index_path;
	char		**array_path;
	char		**array_cmd;

	index_path = search_path(env);
	array_path = ft_split(env[index_path], ':');
	index_path = 0;
	array_cmd = get_arraycmd(cmd, av);
	if (array_cmd[0] == NULL || (av[cmd + 2][0] == '.'
		&& ft_strlen(av[cmd + 2]) == 1))
	{
		free_str(array_cmd);
		free_str(array_path);
		cmd_notfound(pipex);
	}
	if ((access(array_cmd[0], F_OK) == 0 && av[cmd + 2][0] == '/')
			|| ft_strncmp(av[cmd + 2], "./", 2) == 0)
	{
		free_str(array_cmd);
		path = check_path(av, cmd, array_path, pipex);
		return (path);
	}
	path = boucle_path(array_path, array_cmd);
	return (path);
} */
