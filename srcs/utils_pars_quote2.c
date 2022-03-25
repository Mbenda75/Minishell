/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars_quote2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 10:44:12 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/16 22:28:25 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
	// if only same quote for arg echo == skipp 
	//toujour skipp les quote des cmd/arg et des fichier si multi quote = cmd not found
	//si dquote en premier et nb dquote est impair afficher les squote sinon skip tout 
	//si squote en premier et nbquote est impair afficher les dquote sinon skip tout
	//pour echo echo $USER == benmoham 
	//echo  "'''$US'E'R'''" == ''''E'R'''
	//echo ""'''$US'E'R'''"" == $USER
	// echo ""'''"USER"'''"" == "USER"
	//echo """'"USER"'""" == 'USER'
	
int	count_dquote(char *str, int quote)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == 34 && quote == 1)
			size++;
		if (str[i] == 39 && quote == 0)
			size++;
		i++;
	}
	size = size / 2;
	if (size % 2 == 0)
		return (0);
	return (1);
}
