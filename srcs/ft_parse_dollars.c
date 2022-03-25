/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:08:49 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/25 23:52:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_modify_newline_content(char **r_value)
{
	int		i;
	char	*temp;
	char	*str;

	i = 0;
	if (ft_len(r_value) > 1)
	{
		temp = "";
		while (r_value[i])
		{
			str = r_value[i];
			temp = ft_strjoin(temp, str);
			i++;
		}
		return (temp);
	}
	else if (ft_len(r_value) == 1)
		str = r_value[0];
	return (str);
}

char	**ft_transform_dollar_malloc(char *str)
{
	char	**malloc_str;

	malloc_str = malloc(sizeof(char *) * ft_count_dollar(str) + 1);
	return (malloc_str);
}

char	*ft_assign_value(char *s_byspace, char **r_value, t_decompte *index)
{
	char	*word;
	char	**s_bydollar;

	word = s_byspace;
	index->l = -1;
	if (ft_find_dollars(word) == SUCCESS)
	{
		s_bydollar = ft_split(word, '$');
		while (s_bydollar[++index->l])
		{
			if (s_bydollar[index->l][0] == '?')
			{
				r_value[index->j] = ft_itoa(g_list->exit_value);
				r_value[index->j] = ft_strjoin(r_value[index->j], s_bydollar[index->l]);
				index->j++;
			}
			else if (ft_check_env_var_existence(s_bydollar[index->l]) == SUCCESS)
			{
				word = ft_change_dollar_var(s_bydollar[index->l]);
				r_value[index->j] = word;
				index->j++;
			}
			else
			{
				r_value[index->j] = "";
				index->j++;
			}
		}
	}
	r_value[index->j] = '\0';
	return (r_value[index->j]);
}

void ft_calculate_dollar(char **r_value, char **s_byspace, t_decompte *index)
{
	int value;
	int op_un;
	int op_deux;

	op_un = g_list->exit_value;
	op_deux = g_list->exit_value;
	if (s_byspace[index->i][0] == '+')
		value = op_un + op_deux;
}

char	*ft_transform_dollar(char *str)
{
	char		**s_byspace;
	char		**r_value;
	t_decompte	index;

	index.i = -1;
	index.j = 0;
	index.l = 0;
	s_byspace = ft_split(str, ' ');
	r_value = ft_transform_dollar_malloc(str);
	while (s_byspace[++index.i])
		ft_assign_value(s_byspace[index.i], r_value, &index);
	return (ft_modify_newline_content(r_value));
}

char	*ft_transform_dollar_for_no_cmd(char *str)
{
	char		**s_byspace;
	char		**r_value;
	t_decompte	index;

	index.i = -1;
	index.j = 0;
	index.l = 0;
	s_byspace = ft_split(str, ' ');
	r_value = ft_transform_dollar_malloc(str);
	while (s_byspace[++index.i])
	{
		ft_assign_value(s_byspace[index.i], r_value, &index);
		if (!ft_strchr(s_byspace[index.i], '$'))
		{
			if (ft_is_operator(s_byspace[index.i][0]) == SUCCESS)
				ft_calculate_dollar(r_value, s_byspace, &index);
		}
	}
	return (ft_modify_newline_content(r_value));
}
