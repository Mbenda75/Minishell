/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:18:17 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/04 17:33:04 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_str(char **s)
{
    int     line;

    line = 0;

    while (s[line])
    {
        free(s[line]);
        line++;
    }
    free(s);
}

void  *free_lst(t_lst_cmd *lst)
{
    t_lst_cmd *tmp;
	
    while (lst)
   	{
		free_str(lst->split_byspace);
		//free_str(lst->env_2);
		tmp = lst;
        lst = lst->next;
        free(tmp);
    }
    return (lst);
}
