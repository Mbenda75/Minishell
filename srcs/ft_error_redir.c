/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:26:11 by user42            #+#    #+#             */
/*   Updated: 2022/03/19 17:36:34 by benmoham         ###   ########.fr       */
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
	printf("COLLE <\n");
	split_by_spa = ft_strtrim(split_by_spa, "<");
	file_open = open(split_by_spa, O_RDONLY);
	if (file_open < 0)
	{
		free(split_by_spa);
		return (ft_custom_error("No such file or directory"));
	}
	free(split_by_spa);
	close (file_open);
	return (SUCCESS);
}

int ft_colle_chevron_normal(char *str)
{
	int i;
	int file_open;

	i = 0;
	printf("COLLE >\n");
	str = ft_strtrim(str, ">");
	file_open = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0755 );
	if (file_open < 0)
	{
		free(str);
		return (ft_custom_error("Error > chevron"));
	}
	close (file_open);
	printf("Creation de %s\n", str);
	free(str);
	return (SUCCESS);
}

int ft_colle_double_chevron_normal(char *str)
{
	int i;
	int file_open;

	i = 0;
	printf("COLLE >>\n");
	str = ft_strtrim(str, ">>");
	file_open = open(str, O_WRONLY | O_APPEND | O_CREAT, 0755 );
	if (file_open < 0)
	{
		free(str);
		return (ft_custom_error("Error > chevron"));
	}
	close (file_open);
	printf("Creation de %s\n", str);
	free(str);
	return (SUCCESS);
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

int ft_pas_colle_chevron(char **str, int i)
{
	int file_open;

	printf("JE SUIS DANS PAS COLLE >\n");
	file_open = open(str[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if (file_open < 0)
		return (ft_custom_error("Error > pas colle"));
	close (file_open);
	printf("Creation de %s\n", str[i]);
	return (SUCCESS);
}

int ft_pas_colle_double_chevron(char **str, int i)
{
	int file_open;

	printf("JE SUIS DANS PAS COLLE >>\n");
	file_open = open(str[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0755);
	if (file_open < 0)
		return (ft_custom_error("Error >> pas colle"));
	close (file_open);
	printf("Creation de %s\n", str[i]);
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

void create_redir(char **tab, int i)
{
//	int i;

//	i = 0;
//	while (tab[i])
//	{
		if (tab[i][0] == '>')
		{
			ft_pas_colle_chevron(tab, i);
			//i++;
		}
		if (tab[i][0] == '>' && tab[i][1] == '>')
		{
			ft_pas_colle_double_chevron(tab, i);
			//i++;
		}
		//i++;
//	}
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
	while (tab[i])
	{
		j = 0;
		create_redir(tab, i);
		while (tab[i][j])
		{
			open_redir(tab, i, j);
			j++;
		}
		i++;
	}
//	ft_pas_colle_chevron_inverse(tab);
//	ft_pas_colle_chevron(tab);
	free_str(tab);
	printf("REUSSITE CHEVRON\n");
	return (SUCCESS);
}