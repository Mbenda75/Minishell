/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:19:30 by user42            #+#    #+#             */
/*   Updated: 2022/03/27 20:59:54 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_no_cmd_dollar_check(char *str)
{
    char **split_byspace;
    char **s_bydollar;
    int i;
    
    i = 0;
    split_byspace = ft_split(str, ' ');
    if (ft_strchr(split_byspace[0], '$'))
    {
        printf("jai split\n");
         s_bydollar = ft_split(str, '$');
        while (s_bydollar[i])
        {
            printf("S BY DOLLAR == %s\n", s_bydollar[i ]);
            if (ft_check_env_var_existence(s_bydollar[i]) == SUCCESS)
            {
                printf("ici\n");
                free_str(split_byspace);
                free_str(s_bydollar);
                return (SUCCESS);
            }
            i++;
        }
        free_str(s_bydollar);
        free_str(split_byspace);
        return(FAILURE);
    }
    free_str(split_byspace);
    return (SUCCESS);
}

char    *ft_no_cmd_dollar(char *str)
{
    char **split_byspace;

    split_byspace = ft_split(str, ' ');
    if (ft_strchr(split_byspace[0], '$'))
        str = ft_transform_dollar_for_no_cmd(str);
    free_str(split_byspace);
    return (str);
}