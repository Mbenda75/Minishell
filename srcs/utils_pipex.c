/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:14 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/27 23:24:45 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_pipex	*init_pipex(char **split_byspace)
{
	t_pipex	*pipex;

	pipex = NULL;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->line_path = search_path(g_list);
	pipex->split_path = ft_split(pipex->line_path, ':');
	pipex->exec_path = boucle_path(pipex->split_path, split_byspace);
	return (pipex);
}

char	*search_path(t_env *lst)
{
	size_t	size;

	size = 5;
	while (lst)
	{
		if (ft_strncmp("PATH=\n", lst->content, size) == 0)
			break ;
		lst = lst->next;
	}
	return (lst->content);
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

char	*boucle_path(char **array_path, char **array_cmd)
{
	char	*path;
	int		index_path;

	index_path = 0;
	while (array_path[index_path])
	{
		path = ft_strcat2(array_path[index_path], array_cmd[0]);
		if (!path)
			break ;
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		index_path++;
	}
	return (NULL);
}
