/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform_redir_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:29:30 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/29 21:11:24 by benmoham         ###   ########.fr       */
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

char	*ft_redir_nrm(char *tampon, t_env *tmp_2)
{
	char	*tampon_2;
	char *tmp;

	if (ft_strchr(tmp_2->content, '<') || ft_strchr(tmp_2->content, '>'))
		ft_free_middle_node(tmp_2);
	else
	{
		tmp = ft_strjoin(tampon, tmp_2->content);
		tampon_2 = ft_strdup(tmp);
		free(tampon);
		free(tmp);
		tampon = ft_strjoin(tampon_2, " ");
		free(tampon_2);
	}
	return (tampon);
}

char	*ft_transform_redirection(char *str)
{
	t_env	*tmp;
	t_env	*tmp_2;
	char	*tampon;
	char	**s_byspace;

	s_byspace = ft_split(str, ' ');
	memset(&tmp, 0, sizeof(tmp));
	tmp = cpy_env_2(s_byspace, tmp);
	tmp_2 = tmp;
	tampon = ft_calloc(sizeof(char), 1);
	while (tmp_2 != NULL)
	{
		tampon = ft_redir_nrm(tampon, tmp_2);
		tmp_2 = tmp_2->next;
	}
	free_env(tmp);
	free_env(tmp_2);
	free_str(s_byspace);
	return (tampon);
}
