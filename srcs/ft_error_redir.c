/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:26:11 by user42            #+#    #+#             */
/*   Updated: 2022/03/17 20:53:14 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



t_redir ft_count_redirection(char *str)
{
    int i;
    t_redir red;

    i = 0;
    red.redirection_normal = 0;
    red.redirection_inverse = 0;
    red.double_red_norm = 0;
    red.double_red_inv = 0;
    while (str[i])
    {
        if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
            red.redirection_inverse++;
        if (str[i] == '<' && str[i + 1] == '<')
            red.double_red_inv++;
        if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')
            red.redirection_normal++;
        if (str[i] == '>' && str[i + 1] == '>')
            red.double_red_norm++;
        i++;
    }
    return (red);
}

int ft_check_chev_errors(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>' && str[i - 1] == '>')
				return (FAILURE);
			if (str[i + 1] == ' ' && str[i + 2] == '>' || str[i + 1] == ' ' && str[i + 2] == '<')
				return (FAILURE);
		}
		if (str[i] == '<')
		{
			if (str[i + 1] == '>' || str[i + 1] == '<' && str[i - 1] == '<')
				return (FAILURE);
			if (str[i + 1] == ' ' && str[i + 2] == '>' || str[i + 1] == ' ' && str[i + 2] == '<')
				return (FAILURE);
		}
	}
	
	printf("str[i - 1] == [%c]\nstr[i] == [%c]\n", str[i - 1], str[i]);
	if (str[i - 1] == '<' || str[i - 1] == '>' ||  str[i - 1] == ' ')
		return (FAILURE);
	printf("SUCCESS CHECK REDIR\n");
	return (SUCCESS);
}

int ft_colle_chevron_inverse(char *split_by_spa)
{
	int i;
	int file_open;

	i = 0;
	printf("COUCOU <\n");
	split_by_spa = ft_strtrim(split_by_spa, "<");
	file_open = open(split_by_spa, O_RDONLY);
	if (file_open < 0)
		return (ft_custom_error("No such file or directory"));
	close (file_open);
	return (SUCCESS);
}

int ft_colle_chevron_normal(char *str)
{
	int i;
	int file_open;

	i = 0;
	printf("COUCOU >\n");
	str = ft_strtrim(str, ">");
	file_open = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0755 );
	if (file_open < 0)
		return (ft_custom_error("Error > chevron"));
	close (file_open);
	return (SUCCESS);
}

int ft_colle_double_chevron_normal(char *str)
{
	int i;
	int file_open;

	i = 0;
	printf("COUCOU >>\n");
	str = ft_strtrim(str, ">>");
	file_open = open(str, O_WRONLY | O_APPEND | O_CREAT, 0755 );
	if (file_open < 0)
		return (ft_custom_error("Error > chevron"));
	close (file_open);
	return (SUCCESS);
}

void open_redir(char **tab, int i, int j)
{
	if (tab[i][j] == '>' && tab[i][j + 1] != '>')
	{
		ft_colle_chevron_normal(tab[i]);
		j++;
	}
	if (tab[i][j] == '>' && tab[i][j + 1] == '>')
	{
		ft_colle_double_chevron_normal(tab[i]);
		j++;
	}
	if (tab[i][j] == '<' && tab[i][j + 1] != '<') 
	{
		ft_colle_chevron_inverse(tab[i]);
		j++;
	}
	if (tab[i][j] == '>' && tab[i][j + 1] == '>')
	{
		ft_colle_double_chevron_normal(tab[i]);
		j++;
	}
	if (tab[i][j] == '<' && tab[i][j + 1] != '<') 
	{
		ft_colle_chevron_inverse(tab[i]);
		j++;
	}
}

int ft_pas_colle_chevron_inverse(char **str)
{
	int i;
	int file_open;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "<") == 0)
		{
			file_open = open(str[i + 1], O_RDONLY);
			if (file_open < 0)
				return (ft_custom_error("No such file or directory"));
			close (file_open);
			str[i] = NULL;
			str[i + 1] = NULL;
			i = i + 1;
		}
		i++;
	}
	return (SUCCESS);
}

int ft_pas_colle_chevron(char **str)
{
	int i;
	int file_open;

	i = -1;
	while (str[++i])
	{
		if (ft_strcmp(str[i], ">") == 0)
		{
			printf("coucou\n");
			file_open = open(str[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0755);
			if (file_open < 0)
				return (ft_custom_error("Error > chevron"));
			close (file_open);
			i = i + 2;
		}
		else if (ft_strcmp(str[i], ">>") == 0)
		{
			printf("coucou 2\n");
			file_open = open(str[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0755);
			if (file_open < 0)
				return (ft_custom_error("Error >> chevron"));
			close (file_open);
			i = i + 2;
		}
	}
	return (SUCCESS);
}

int	ft_check_redirection(char *str)
{
	char **tab;
	int i;
	int j;
	
	i = 0;
	j = 0;
	tab = NULL;
 	if (ft_check_chev_errors(str) == 1)
	{
		printf("ERROR CHEVRON\n");
		return (FAILURE);
	}
	tab = ft_split(str, ' ');
/*	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			open_redir(tab, i, j);
			j++;
		}
		i++;
	}*/
	ft_pas_colle_chevron_inverse(tab);
	ft_pas_colle_chevron(tab);
	ft_free_charr(tab);
	printf("REUSSITE CHEVRON\n");
	return (SUCCESS);
}
