/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:27:19 by user42            #+#    #+#             */
/*   Updated: 2022/03/21 21:56:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_check_if_no_redir(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '>')
            return (SUCCESS);
        if (str[i] == '<')
            return (SUCCESS);
    }
    return (FAILURE);
}

int ft_check_chevron_grammar_1(char *str)
{
    int i;
    int check;

    i = -1;
    check = 0;
    while (str[++i])
    {
        if (str[i] == '>')
        {
            i++;
            if (str[i] == '>')
                i++;
            while (str[i] == ' ')
                i++;
            if (str[i] == '>' || str[i] == '<')
                check = 1;
        }
    }
    if (check == 1)
    {
        printf("syntax error near unexpected token\n");
        return (FAILURE);
    }
    return (SUCCESS);
}

int ft_check_chevron_grammar_2(char *str)
{
    int i;
    int check;

    i = -1;
    check = 0;
    while (str[++i])
    {
        if (str[i] == '<')
        {
            i++;
            if (str[i] == '<')
                i++;
            while (str[i] == ' ')
                i++;
            if (str[i] == '<' || str[i] == '>')
                check = 1;
        }
    }
    if (check == 1)
    {
        printf("syntax error near unexpected token\n");
        return (FAILURE);
    }
    return (SUCCESS);
}

int ft_check_space_at_the_end(char *str)
{
    int i;
    int j;

    i = ft_strlen(str) - 1;
    if (str[i] == '<' || str[i] == '>')
		return (ft_custom_error("syntax error near unexpected token newline"));
    if (str[i] == ' ')
    {
        while (str[i] == ' ')
            i--;
        if (str[i] == '>' | str[i] == '<')
            return (ft_custom_error("syntax error near unexpected token newline"));
    }
    return (SUCCESS);
}

int ft_check_all_redir_errors(char *str)
{
    if (ft_check_if_no_redir(str) == FAILURE)
        return (FAILURE);
    if (ft_check_chevron_grammar_1(str) == FAILURE)
        return (FAILURE);
    if (ft_check_chevron_grammar_2(str) == FAILURE)
        return (FAILURE);
    if (ft_check_space_at_the_end(str) == FAILURE)
        return (FAILURE);
    return (SUCCESS);
}