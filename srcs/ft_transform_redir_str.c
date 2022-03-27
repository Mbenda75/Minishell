/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform_redir_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:29:30 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/27 20:01:40 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*fill_env_2(char *str)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	lst->content = str;
	lst->next = NULL;
	return (lst);
}

t_env	*cpy_env_2(char **s_byspace, t_env *r_value)
{
	t_env	*tmp;
	int		i;

	tmp = r_value;
	i = 0;
	while (s_byspace[i])
	{
		if (!r_value)
		{
			r_value = fill_env_2(ft_strdup(s_byspace[i]));
			tmp = r_value;
		}
		else
		{
			tmp->next = fill_env_2(ft_strdup(s_byspace[i]));
			tmp = tmp->next;
		}
		i++;
	}
	return (r_value);
}

void	ft_free_middle_node_2(t_env *head)
{
	t_env	*tmp;

	tmp = head->next;
	free(head->content);
	head->content = head->next->content;
	head->next = head->next->next;
	free(tmp);
}

void	ft_free_last_node_2(t_env *temp)
{
	while (temp->next->next != NULL)
		temp = temp->next;
	free(temp->next->content);
	free(temp->next);
	temp->next = NULL;
}

char *ft_transform_redirection(char *str)
{
	t_env *tmp;
	t_env *tmp_2;
	char *tampon;
	char *tampon_2;
	char **s_byspace;

	s_byspace = ft_split(str, ' ');
	memset(&tmp, 0, sizeof(tmp));
	tmp = cpy_env_2(s_byspace, tmp);
	tmp_2 = tmp;
	tampon = ft_calloc(sizeof(char), 1);
	while (tmp_2 != NULL)
	{
		if (ft_strchr(tmp_2->content, '<') || ft_strchr(tmp_2->content, '>'))
		{
			ft_free_middle_node_2(tmp_2);
			tmp_2 = tmp_2->next;
		}
		else
		{
			tampon = ft_strjoin(tampon, tmp_2->content);
			tampon_2 = ft_strdup(tampon);
			tampon = ft_strjoin(tampon_2, " ");
			free(tampon_2);
			tmp_2 = tmp_2->next;
		}
	}
	free(tmp);
	free(tmp_2);
	free_str(s_byspace);
	return (tampon);
}