/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:24:58 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/05 20:07:02 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

	//toujour skipp les quote des cmd/arg et des fichier si multi quote = cmd not found
	//si dquote en premier et nb dquote est impair afficher les squote sinon skip
	//si squote en premier et nbquote est impair afficher les dquote sinon skip


int count_dquote(char *str, int quote)
{
	int i;
	
	int size;

	i = 0;
	size = 0;
	while(str[i])
	{
		if (str[i] == 34 && quote == 1)
			size++;
		if (str[i] == 39 && quote == 0)
			size++;
		i++;
	}
	if (size % 2 == 0)
		return (0);
	return (1);
}

char *parse_echo_arg(char *str)
{
	int i;
	int nb_quote;
	char *new_str;

	nb_quote =0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34) // dquote
		{
			if (count_dquote(str, 1) == 0)
			{
				new_str = skip_squote_cmd(str);
				return (new_str);
			}
		}
		if (str[i] == 39) // squote
		{
			if (count_dquote(str, 0) == 0)
			{
				new_str = skip_dquote_cmd(str);
				return (new_str);
			}
		}
		i++;
	}
	return (NULL);
}