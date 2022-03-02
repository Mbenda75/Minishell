/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:46:47 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/02 17:43:32 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_lst_cmd	*file_lst(char *split_bypipe)
{
	t_lst_cmd *lst;
	
	lst = malloc(sizeof(t_lst_cmd));
	lst->split_byspace = ft_split(split_bypipe, ' ');
	lst->
	lst->next= NULL;
 	for (int i = 0; lst->split_byspace[i];i++)
	printf("split by pipe== %s\n", lst->split_byspace[i]);
	return (lst);
}

t_lst_cmd	*create_lst(char *str, t_lst_cmd *lst, int nb_pipe)
{
	int i;
	char **split_bypipe;
	t_lst_cmd *tmp;
	
	tmp = NULL;
	i = 0;
	if (nb_pipe != 0)
		split_bypipe = ft_split(str, '|');
	while (i <= nb_pipe)
	{
		if (!lst)
		{
			printf("icisg\n");
			if (nb_pipe != 0)
				lst = file_lst(split_bypipe[i]);
			else
				lst = file_lst(str);
			tmp = lst;
		}
		else
		{
			printf("ici2\n");
			tmp->next = file_lst(split_bypipe[i]);
			tmp = tmp->next;
		}
		i++;
	}
	if (nb_pipe != 0)
		free_str(split_bypipe);
	return (lst);
}