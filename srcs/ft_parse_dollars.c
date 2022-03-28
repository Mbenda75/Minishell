/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:08:49 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/28 15:41:10 by adaloui          ###   ########.fr       */
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
		printf("temp == %s\n", temp);
		return (temp);
	}
	else if (ft_len(r_value) == 1)
		str = r_value[0];
	return (str);
}

char	**ft_transform_dollar_malloc(char *str)
{
	char	**malloc_str;

	malloc_str = malloc(sizeof(char *) * ft_strlen(str) + 1);
	return (malloc_str);
}

char *ft_assign_value_2(char **s_bydollar, t_decompte *index)
{
	char *tmp;
	char *word;

	if (s_bydollar[index->l][0] == '?')
	{
		tmp = ft_itoa(g_list->exit_value);
		word = ft_strjoin(tmp, s_bydollar[index->l] + 1);
		free(tmp);
	}
	else if (ft_check_env_var_existence(s_bydollar[index->l]) == 0)
		word = ft_change_dollar_var(s_bydollar[index->l]);
	else
	{
		if (index->l != 0)
			word  = "";
		else
			word = ft_strdup(s_bydollar[0]);
	}
	return (word);
}

char	**ft_assign_value(char *s_byspace, char **r_value, t_decompte *index)
{
	char	**s_bydollar;

	index->l = -1;
	if (ft_find_dollars(s_byspace) == SUCCESS)
	{
		s_bydollar = ft_split(s_byspace, '$');
		while (s_bydollar[++index->l])
			r_value[index->j++] = ft_assign_value_2(s_bydollar, index);
	}
	free_str(s_bydollar);
	r_value[index->j] = '\0';
	return (r_value);
}

char	*ft_transform_dollar(char *str)
{
	char		**s_byspace;
	char		**r_value;
	char 	**tmp;
	char	*tmp2;
	t_decompte	index;

	index.i = -1;
	index.j = 0;
	index.l = 0;
	s_byspace = ft_split(str, ' ');
	r_value = ft_transform_dollar_malloc(str);
	while (s_byspace[++index.i])
		ft_assign_value(s_byspace[index.i], r_value, &index);
	if (str[0] != '$')
	{
		tmp = ft_split(str, '$');
		tmp2 = ft_modify_newline_content(r_value);
		tmp2 = ft_strjoin(tmp[0], tmp2);
		free_str(tmp);
		return (tmp2);
	}
	tmp2 =  ft_modify_newline_content(r_value);
	return (tmp2);
}

char	*ft_transform_dollar_for_no_cmd(char *str)
{
	char		**s_bydollar;
	char		**r_value;
	char		*tmp;
	t_decompte	index;
	int			i;

	index.i = -1;
	index.j = 0;
	index.l = 0;
	i = 0;
	s_bydollar = ft_split(str, '$');
	while (s_bydollar[i])
	{
		if (ft_check_env_var_existence(s_bydollar[i]) == SUCCESS)
		{
			r_value = ft_transform_dollar_malloc(str);
			r_value = ft_assign_value(str, r_value, &index);
			tmp = ft_modify_newline_content(r_value);
			free_str(s_bydollar);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}
