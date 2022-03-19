/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:18:17 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/16 22:17:42 by benmoham         ###   ########.fr       */
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
		free(tmp->content);
		lst = lst->next;
		free(tmp);
	}
	return (lst);
}
