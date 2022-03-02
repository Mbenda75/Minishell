/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:32:13 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/02 16:45:12 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_pipe(char *str)
{
	int i;
	int pipe;

	i = 0;
	pipe = 0;
	while(str[i])
	{
		if (str[i] == '|')
			pipe++;
		i++;
	}
	return (pipe);
}

int if_noquote(char *str)
{
	int i;
	int quote;

	quote = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == 34)
			quote++;
		i++;
	}
	if (quote % 2)
		return (0);
	return (1);
}
/* 
char	*skip_dquote_arg(char *str)
{
	int i;
	int start;
	char *new_str;
	
	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			start = i;
			while (str[i] != 34)
				i++;
			new_str = ft_substr(str, start, i - start);
			return (new_str);
		}
		i++;
	}
	return (str);
} */

int size_malloc(char *str)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while(str[i])
	{
		if (str[i] != 34 || str[i] != 39)
			size++;
		i++;	
	}
	return (size);
}

char	*skip_dquote(char *str)
{
	int i;
	int size;
	int j;
	char *new_str;
	
	i = 0;
	j = 0;
	size = size_malloc(str);
	new_str = malloc(sizeof(char *) * size + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			i++;
		new_str[j] = str[i];
		j++;
		i++; 
	}
	new_str[j] = '\0';
	return (new_str);
}