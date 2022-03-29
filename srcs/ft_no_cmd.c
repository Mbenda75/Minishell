/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:19:30 by user42            #+#    #+#             */
/*   Updated: 2022/03/29 17:29:09 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_no_cmd_dollar_check(char **str)
{
	char	**s_bydollar;
	int		i;

	i = 0;
	if (ft_strchr(str[0], '$'))
	{
		s_bydollar = ft_split(str[0], '$');
		while (s_bydollar[i])
		{
			if (ft_check_env_var_existence(s_bydollar[i]) == SUCCESS)
			{
				free_str(s_bydollar);
				return (SUCCESS);
			}
			i++;
		}
		free_str(s_bydollar);
		return (FAILURE);
	}
	return (SUCCESS);
}

char	*ft_no_cmd_dollar(char *str)
{
	char *tmp;
	char **tab;
	tab = ft_split(str, ' ');
	if (ft_strchr(tab[0], '$'))
	{
		printf("ici\n");
		tmp = ft_transform_dollar_for_no_cmd(str);
		free_str(tab);
		return (tmp);
	}
	free_str(tab);
	tmp = ft_strdup(str);
	return (tmp);
}
