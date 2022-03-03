/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:18:17 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/03 19:38:48 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_str(char **s)
{
    int     line;

    line = 0;

    for (int i = 0; s[i];i++)
    printf("split by pipe== %s\n", s[i]);
    while (s[line])
    {
	    
        printf("line %d \n", line);
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
		tmp = lst;
        lst = lst->next;
        free(tmp);
    }
    return (lst);
}
