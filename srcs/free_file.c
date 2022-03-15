/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:18:17 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/15 18:38:53 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_str(char **s)
{
	int	line;

	line = 0;
	while (s[line])
	{
		free(s[line]);
		line++;
	}
	free(s);
}

void	*free_lst(t_lst_cmd *lst)
{
	t_lst_cmd	*tmp;

	while (lst != NULL)
	{
		free_str(lst->split_byspace);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	return (lst);
}

void	*free_env(t_env *lst)
{
	t_env	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		if (tmp->index_env >= g_list->limit_free)
			free(tmp->content);
		lst = lst->next;
		free(tmp);
	}
	return (lst);
}
