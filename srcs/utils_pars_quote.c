/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:32:13 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/28 18:53:40 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>

int	check_first_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
			return (1);
		if (str[i] == 39)
			return (2);
		i++;
	}
	return (0);
}

int	if_noquote(char *str)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			quote++;
		i++;
	}
	if (quote % 2 == 0)
		return (SUCCESS);
	else
	{
		printf("Error quote\n");
		return (FAILURE);
	}
}

int	size_malloc(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != 34 || str[i] != 39)
			size++;
		i++;
	}
	return (size);
}

char	*skip_quote_norm(char *str, char *new_str, t_decompte *index)
{
	if (str[index->i] == '\'' || str[index->i] == '"')
	{
		index->l = index->i;
		index->i++;
		while (str[index->i] && str[index->i] != str[index->l])
		{
			new_str[index->j++] = str[index->i];
			index->i++;
		}
		index->i++;
	}
	else
	{
		new_str[index->j++] = str[index->i];
		index->i++;
	}
	return (new_str);
}

char	*skip_quote(char *str)
{
	t_decompte	index;
	char		*new_str;

	index.i = 0;
	index.j = 0;
	if (ft_strchr(str, 34) || ft_strchr(str, 39))
	{
		new_str = malloc(sizeof(char) * ft_strlen(str) + 1);
		if (!new_str)
			return (NULL);
		while (str[index.i])
			new_str = skip_quote_norm(str, new_str, &index);
		new_str[index.j++] = '\0';
		return(new_str);
	}
	return (str);
}
