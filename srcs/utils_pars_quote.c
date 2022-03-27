/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:32:13 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/27 21:10:08 by adaloui          ###   ########.fr       */
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
	printf("quote == %d\n", quote);
	if (quote % 2 == 0)
		return (SUCCESS);
	else
	{
		printf("error quote\n");
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

char	*skip_quote(char *str)
{
	int		temp;
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);

		
	printf("STR === %s\n", str);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			temp = i;
			i++;
			while (str[i] && str[i] != str[temp])
			{
				new_str[j++] = str[i];
				i++;
			}
			i++;
		}
		else
		{
			new_str[j++] = str[i];
			i++;
		}
		
	}
	new_str[j++] = '\0';
	return (new_str);
}
