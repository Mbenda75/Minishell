/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:32:13 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/04 18:15:03 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_quote(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == 34)
			return (1);
		if (str[i] == 39)
			return (2);
		i++;
	}
	return (0);
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

char	*skip_squote_cmd(char *str)
{
	int i;
	int j;
	char *new_str;
	
	i = 0;
	j = 0;

	new_str = malloc(sizeof(char *) * ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 39)
			i++;
		new_str[j] = str[i];
		j++;
		i++; 
	}
	new_str[j] = '\0';
	return (new_str);
} 

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

char	*skip_dquote_cmd(char *str)
{
	int i;
	int j;
	char *new_str;
	
	i = 0;
	j = 0;
	new_str = malloc(sizeof(char *) * ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 34)
			i++;
		new_str[j] = str[i];
		j++;
		i++; 
	}
	new_str[j] = '\0';
	return (new_str);
}