/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:08:49 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/22 19:31:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_checK_env_var_existence(char *complete_var)
{
    t_env *verify;
    char *tmp_add_equal;

    verify = g_list;
    tmp_add_equal = ft_strjoin(complete_var, "=");
    while (verify)
    {
        if (ft_strncmp(verify->content, tmp_add_equal, ft_strlen(tmp_add_equal)) == SUCCESS)
        {
            free(tmp_add_equal);
            return (SUCCESS);
        }
        verify = verify->next;
    }
    free(tmp_add_equal);
    return (FAILURE);
}

char *ft_change_dollar_var(char *word)
{
    t_env *verify;
    char *tmp_add_equal;

    verify = g_list;
    tmp_add_equal = ft_strjoin(word, "=");
    while (verify)
    {
        if (ft_strncmp(verify->content, tmp_add_equal, ft_strlen(tmp_add_equal)) == SUCCESS)
        {
            word = ft_substr(verify->content, ft_find_where_is_equal(verify->content) + 1, ft_strlen(verify->content));
            free(tmp_add_equal);
            return (word);
        } 
        verify = verify->next; 
    }
    free(tmp_add_equal);
    return (word);
}
/* Sers a join toutes les var dans une seule string*/
char *ft_modify_newline_content(char **receive_value)
{
    int i;
    char *temp;
    char *str;
    i = 0;
     
    if (receive_value[i + 1])
    {
        temp = "";
        while (receive_value[i])
        {
            str = receive_value[i];
            temp = ft_strjoin(temp, str);
            i++;
        }
       return (temp);
    }
    else if (receive_value[i + 1] == NULL) 
        str = receive_value[0];
    return (str);
}

int	count_dollar(char *str)
{
	int	i;
	int	dollar;

	i = 0;
	dollar = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$')
			dollar++;
		i++;
	}
	return (dollar);
}

char *ft_transform_dollar(char *str)
{
    int i;
    int j;
    char *word;
    char **split_byspace;
    char **split_bydollar;
    char **receive_value;
    int k;

    i = -1;
    j = 0;
    int dollar = count_dollar(str);
    split_byspace = ft_split(str, ' ');
    receive_value = malloc(sizeof(char *) * count_dollar(str) + 1);
    while (split_byspace[++i])
    {
        word = split_byspace[i];
        k = 0;
        if (ft_find_dollars(word) == SUCCESS)
        {
            split_bydollar = ft_split(word, '$');
            while (split_bydollar[k])
            {
                if (ft_checK_env_var_existence(split_bydollar[k]) == SUCCESS)
                {
                    word = ft_change_dollar_var(split_bydollar[k]);
                    receive_value[j] = word;
                    j++;
                }
                else
                {
                    receive_value[j] = "";
                    j++;
                }
                k++;
            }
            receive_value[j] = '\0';
        }
        else
        {
            receive_value[j] = word;
            receive_value[j] = ft_strjoin(receive_value[j], " ");
            j++;
        }
    }
    return (ft_modify_newline_content(receive_value));

}