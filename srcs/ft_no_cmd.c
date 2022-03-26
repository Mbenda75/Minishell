/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:19:30 by user42            #+#    #+#             */
/*   Updated: 2022/03/26 15:22:23 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_no_cmd_dollar_check(char *str)
{
    char **split_byspace;    

    split_byspace = ft_split(str, ' ');
    if (ft_strchr(split_byspace[0], '$'))
    {
        str = ft_transform_dollar_for_no_cmd(str);
        if (str == NULL)
        {
            free_str(split_byspace);
            return (FAILURE);
        }
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