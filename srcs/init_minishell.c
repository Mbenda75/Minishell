/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:19:35 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/25 20:28:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*fill_lst(char *str)
{
	t_lst_cmd	*lst;
	int i;

	i = 1;
	lst = malloc(sizeof(t_lst_cmd));
	if (!lst)
		return(NULL);
	lst->split_byspace = ft_split(str, ' ');
	while (lst->split_byspace[i])
	{
		
		if (lst->split_byspace[i][0] == '>' && lst->split_byspace[i][1] != '>')
		{
			lst->split_byspace[i] = NULL;
			i++;
		}
		if (lst->split_byspace[i][0] == '>' && lst->split_byspace[i][1] == '>')
		{
			lst->split_byspace[i] = NULL;
			i++;
		}
		if (lst->split_byspace[i][0] == '<' && lst->split_byspace[i][1] != '<')
		{
			lst->split_byspace[i] = NULL;
			i++;
		}
		if (lst->split_byspace[i][0] == '<' && lst->split_byspace[i][1] == '<')
		{
			lst->split_byspace[i] = g_list->ret_herdc;
			i++;
		}
		i++;
	}
	printf("JE SUIS LA\n");
	i = 0;
	while (lst->split_byspace[i])
	{
		printf("split == %s\n", lst->split_byspace[i]);
		i++;
	}
	lst->pipex = init_pipex(lst->split_byspace);
	lst->next = NULL;
	return (lst);
}

t_lst_cmd	*create_norm(t_lst_cmd *lst, char **split_bypipe, char *prompt_line)
{
	int			i;
	t_lst_cmd	*tmp;
	
	i = -1;
	while (++i <= g_list->nb_pipe)
	{
		if (!lst)
		{
			if (g_list->nb_pipe != 0)
				lst = fill_lst(split_bypipe[i]);
			else
				lst = fill_lst(prompt_line);
			tmp = lst;
		}
		else
		{
			tmp->next = fill_lst(split_bypipe[i]);
			tmp = tmp->next;
		}
	}
	return (lst);
}

t_lst_cmd	*create_lst(char *prompt_line, t_lst_cmd *lst)
{
	char	**split_bypipe;

	if (g_list->nb_pipe != 0)
		split_bypipe = ft_split(prompt_line, '|');
	lst = create_norm(lst, split_bypipe, prompt_line);
	if (g_list->nb_pipe != 0)
		free_str(split_bypipe);
	return (lst);
}

t_lst_cmd	*init_shell(char *buffer, t_lst_cmd *lst)
{
	if (ft_check_if_no_redir(buffer) == SUCCESS)
		ft_redir_handler(buffer);
	if (g_list->nb_pipe != 0)
		lst = create_lst(buffer, lst);
	else if (g_list->nb_pipe == 0)
		lst = create_lst(buffer, lst);
	return (lst);
}
