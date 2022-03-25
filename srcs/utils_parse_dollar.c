/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:06:47 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/25 23:06:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_dollar(char *str)
{
	int	i;
	int	dollar;

	i = 0;
	dollar = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$')
			dollar++;
		i++;
	}
	return (dollar);
}

int	ft_check_env_var_existence(char *complete_var)
{
	t_env	*check;
	char	*tmp_add_equal;

	check = g_list;
    if (ft_strcmp(complete_var, "?") == 0)
	{
        return (SUCCESS);
	}
	tmp_add_equal = ft_strjoin(complete_var, "=");
	while (check)
	{
		if (ft_strncmp(check->content, tmp_add_equal,
				ft_strlen(tmp_add_equal)) == SUCCESS)
		{
			free(tmp_add_equal);
			return (SUCCESS);
		}
		check = check->next;
	}
	free(tmp_add_equal);
	return (FAILURE);
}

char	*ft_change_dollar_var(char *word)
{
	t_env	*check;
	char	*tmp_add_equal;

	check = g_list;
    if (ft_strcmp(word, "?") == 0)
	{
        return (word = ft_itoa(g_list->exit_value));
	}
	tmp_add_equal = ft_strjoin(word, "=");
	while (check)
	{
		if (ft_strncmp(check->content, tmp_add_equal,
				ft_strlen(tmp_add_equal)) == SUCCESS)
		{
			word = ft_substr(check->content,
					ft_find_where_is_equal(check->content) + 1,
					ft_strlen(check->content));
			free(tmp_add_equal);
			return (word);
		}
		check = check->next;
	}
	free(tmp_add_equal);
	return (word);
}

int ft_is_operator(char str)
{
	if (str == '+' || str == '*' || str == '/' || str == '-')
			return (SUCCESS);
	return (FAILURE);
}