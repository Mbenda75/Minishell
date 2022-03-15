/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:59:07 by user42            #+#    #+#             */
/*   Updated: 2022/03/15 19:02:09 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_variable_unset(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (!((cmd[i][j] >= 'a' && cmd[i][j] <= 'z' )
				|| (cmd[i][j] >= 'A' && cmd[i][j] <= 'Z')
				|| (cmd[i][j] == '_')))
				return (ft_custom_error("unset: not valid identifier"));
			j++;
		}
		i++;
	}
	return (0);
}	

void	ft_built_in_unset_2(char *cmd)
{
	t_env	*head;
	t_env	*temp;
	t_env	*lastnode;
	t_env	*tmp;

	head = g_list;
	temp = head;
	cmd = ft_strjoin(cmd, "=");
	while (head != NULL)
	{
		if (ft_strncmp(head->content, cmd, ft_strlen(cmd)) == 0)
		{
			if (head->next != NULL)
			{
				tmp = head->next;
				if (head->index_env >= g_list->limit_free)
					free(head->content);
				head->content = head->next->content;
				head->next = head->next->next;
				free(tmp);
				break ;
			}
			if (head->next == NULL)
			{
				while (temp->next->next != NULL)
					temp = temp->next;
				if (temp->next->index_env >= g_list->limit_free)
					free(temp->next->content);
				free(temp->next);
				lastnode = temp->next;
				temp->next = NULL;
			}
			break ;
		}
		head = head->next;
	}
	free(cmd);
	cmd = NULL;
}

int	ft_built_in_unset(char **cmd)
{
	int	i;
	int	j;

	j = 1;
	if (cmd[1] == NULL)
		ft_putstr_fd("", 0);
	else
	{
		i = ft_check_variable_unset(cmd);
		if (i == 1)
			return (FAILURE);
		while (cmd[j])
		{
			ft_built_in_unset_2(cmd[j]);
			j++;
		}
	}
	return (SUCCESS);
}
