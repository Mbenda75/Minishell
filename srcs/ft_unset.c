/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:59:07 by user42            #+#    #+#             */
/*   Updated: 2022/03/23 14:03:57 by adaloui          ###   ########.fr       */
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
	return (SUCCESS);
}	

void	ft_free_middle_node(t_env *tmp, t_env *head)
{
	tmp = head->next;
	free(head->content);
	head->content = head->next->content;
	head->next = head->next->next;
	free(tmp);
}

void	ft_free_last_node(t_env *temp, t_env *lastnode)
{
	while (temp->next->next != NULL)
		temp = temp->next;
	free(temp->next->content);
	free(temp->next);
	lastnode = temp->next;
	temp->next = NULL;
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
				ft_free_middle_node(tmp, head);
				break ;
			}
			if (head->next == NULL)
				ft_free_last_node(temp, lastnode);
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

	i = 1;
	if (cmd[1] == NULL)
		ft_putstr_fd("", 0);
	else
	{
		if (ft_check_variable_unset(cmd) == FAILURE)
			return (FAILURE);
		while (cmd[i])
		{
			ft_built_in_unset_2(cmd[i]);
			i++;
		}
	}
	return (SUCCESS);
}
