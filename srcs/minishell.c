/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:46:47 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/05 17:14:37 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_lst_cmd	*file_lst(char *split_bypipe, char **env)
{
	t_lst_cmd *lst;
	
	lst = malloc(sizeof(t_lst_cmd));
	lst->split_byspace = ft_split(split_bypipe, ' ');
	lst->next= NULL;
 /*	for (int i = 0; lst->split_byspace[i];i++)
	printf("split by pipe== %s\n", lst->split_byspace[i]);*/
	return (lst);
}

t_lst_cmd	*create_lst(char *prompt_line, int nb_pipe, t_lst_cmd *lst, char **env)
{
	int i;
	char **split_bypipe;
	t_lst_cmd *tmp;
	
	tmp = NULL;
	i = 0;
	if (nb_pipe != 0)
		split_bypipe = ft_split(prompt_line, '|');
	while (i <= nb_pipe)
	{
		if (!lst)
		{
			if (nb_pipe != 0)
				lst = file_lst(split_bypipe[i], env);
			else
				lst = file_lst(prompt_line, env);
			tmp = lst;
		}
		else
		{
			tmp->next = file_lst(split_bypipe[i], env);
			tmp = tmp->next;
		}
		i++;
	}
	if (nb_pipe != 0)
		free_str(split_bypipe);
	return (lst);
}

t_lst_cmd	*init_shell(char *buffer, t_lst_cmd *lst, char **env)
{
	int		nb_pipe;
	
	nb_pipe = count_pipe(buffer);
	if (nb_pipe != 0)
	{
		/* parsing de plusieur commande */
	  	lst = create_lst(buffer, nb_pipe, lst, env);
		
	}
	else if (nb_pipe == 0)
	{
		lst = create_lst(buffer, 0, lst, env); 
		/* parser une seul commande et execution*/
	}
	return (lst);
}