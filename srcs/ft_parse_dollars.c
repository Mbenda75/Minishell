/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:08:49 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/26 15:28:54 by adaloui          ###   ########.fr       */
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

	malloc_str = malloc(sizeof(char *) * ft_strlen(str) + 1);
	return (malloc_str);
}

char	**ft_assign_value(char *s_byspace, char **r_value, t_decompte *index)
{
	char	*word;
	char *tmp;
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
				tmp	= ft_itoa(g_list->exit_value);
				r_value[index->j] = ft_strjoin(tmp, s_bydollar[index->l] + 1);
				free(tmp);
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
	free_str(s_bydollar);
	r_value[index->j] = '\0';
	return (r_value);
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
	char		**s_bydollar;
	char		**r_value;
	char *tmp;
	t_decompte	index;
	int			i;

	index.i = -1;
	index.j = 0;
	index.l = 0;
	i = 0;
	s_bydollar = ft_split(str, '$');
	while (s_bydollar[i])
	{
		printf("S BY DOLLAR == %s\n", s_bydollar[i ]);
		if (ft_check_env_var_existence(s_bydollar[i]) == SUCCESS)
		{
			r_value = ft_transform_dollar_malloc(str);
			r_value = ft_assign_value(str, r_value, &index);
			free_str(s_bydollar);
			tmp = ft_modify_newline_content(r_value);
			//free_str(r_value);
			return (tmp);
		}
		i++;
	}
	printf("Sortie BY DOLLAR == %s\n", s_bydollar[i - 1]);
	return(NULL);
}
