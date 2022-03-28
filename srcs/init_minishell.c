/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:19:35 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/28 17:36:43 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*fill_lst(char *str)
{
	t_lst_cmd	*lst;

	lst = malloc(sizeof(t_lst_cmd));
	if (!lst)
		return (NULL);
	lst->split_byspace = ft_split(str, ' ');
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
	{
		ft_redir_handler(buffer);
		buffer = ft_transform_redirection(buffer);
		g_list->check_stds = 1;
	}
	else
		g_list->check_stds = 0;
	if (g_list->nb_pipe != 0)
		lst = create_lst(buffer, lst);
	else if (g_list->nb_pipe == 0)
		lst = create_lst(buffer, lst);
	return (lst);
}
