/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:19:30 by user42            #+#    #+#             */
/*   Updated: 2022/03/26 00:01:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void    ft_handle_dollar_no_cmd(char **split_byspace)
{
    int i;
    int j;
    
    i = 0;
    while (split_byspace[i])
    {
        j = 0;
        while (split_byspace[i][j])
        {
            if (split_byspace[i][j] == '$' && split_byspace[i][j + 1] == '?')
                split_byspace[i] = ft_itoa(g_list->exit_value);
            if (split_byspace[i][j] == '$' && split_byspace[i][j + 1] != '?')
                split_byspace[i] = ft_transform_dollar(split_byspace[i]);
                
            j++;
        }
        i++;
    }
    
    
}

int	check_env_no_cmd(char *complete_var)
{
	t_env	*check;
	char	*tmp_add_equal;

	check = g_list;
    if (ft_strcmp(complete_var, "?") == 0)
	{
        return (SUCCESS);
	}
    
	tmp_add_equal = ft_strjoin(complete_var, "=");
	while (check)
	{
		if (ft_strncmp(check->content, tmp_add_equal,
				ft_strlen(tmp_add_equal)) == SUCCESS)
		{
			free(tmp_add_equal);
			return (SUCCESS);
		}
		check = check->next;
	}
	free(tmp_add_equal);
	return (FAILURE);
}

char    *ft_no_cmd_dollar(char *str)
{
    char **split_byspace;
    char **split_bydollar;
    int i;
    char *word;

    i = -1;
    split_byspace = ft_split(str, ' ');
    if (ft_strchr(split_byspace[0], '$'))
    {
        split_bydollar = ft_split(str, '$');
        printf("OK\n");
        while (split_bydollar[++i])
        {
            printf("OK 1\n");
            printf("split_by dollar = %s\n", split_bydollar[i]);
            if (check_env_no_cmd(split_bydollar[i]) == SUCCESS)
                break ;
            else 
            {
                free_str(split_bydollar);
                return (str);
            }
        }
        free_str(split_bydollar);
        printf("OK 3\n");
        str = ft_transform_dollar_for_no_cmd(str);
    }
    free_str(split_byspace);
    return (str);
}