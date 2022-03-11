/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:14 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/10 16:42:45 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *search_path(t_env *lst)
{
	size_t	size;
	int		index_path;
	char *str;

	size = 5;
	index_path = 0;
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
	int index_path;

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