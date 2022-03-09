/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:26:11 by user42            #+#    #+#             */
/*   Updated: 2022/03/09 14:07:15 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_strchevroncmp(char **str, char c)
{
	int i;
	int j;
	int n;
	int compteur;

	i = 0;
	compteur = 0;
	while (str[i])
	{
		j = 0;
		n = ft_strlen(str[i]);
		while (str[i][j] && j < n)
		{
			if (str[i][j] == c)
				compteur++;
			j++;
		}
		i++;
	}
	return (compteur);
}

int ft_strdblchevroncmp(char **str, char *c)
{
	int i;
	int j;
	int n;
	int compteur;

	i = 0;
	compteur = 0;
	while (str[i])
	{
		n = 2;
		if (ft_strncmp(str[i], c, 2) == 0)
			compteur++;
		i++;
	}
	return (compteur);
}

int	ft_count_chevron(char **str, int k, t_decompte m)
{
	while (str[m.i])
	{
		m.j = 0;
		while (str[m.i][m.j])
		{
			if (str[m.i][m.j] == '>')
			{
				k++;
				if (k >= 3)
				{
					printf("Syntax error with '>>>'\n");
					return (FAILURE);
				}

			}
			if (str[m.i][m.j] == '<')
			{
				m.l++;
				if (m.l >= 3)
				{
					printf("Syntax error with '<<<'\n");
					return (FAILURE);
				}
			}
			m.j++;
		}
		m.i++;
	}
	return (SUCCESS);
}

int ft_check_chev_errors(char **str)
{
	t_decompte m;
	int k;

	m.i = 0;
	k = 0;
	m.l = 0;
	if (str[0][0] == '<')
	{
		printf("Syntax error with '<'\n");
		return (FAILURE);
	}
	if (str[0][0] == '<' && str[0][1] == '<')
	{
		printf("Syntax error with '<<'\n");
		return (FAILURE);
	}
	ft_count_chevron(str, k, m);
	while (str[m.i])
	{
		m.j = 0;
		while (str[m.i][m.j])
		{
			if (str[m.i][m.j] == '>')
			{
				k++;
				if (k >= 3)
				{
					printf("Syntax error with '>>>'\n");
					return (FAILURE);
				}

			}
			if (str[m.i][m.j] == '<')
			{
				m.l++;
				if (m.l >= 3)
				{
					printf("Syntax error with '<<<'\n");
					return (FAILURE);
				}
			}
			m.j++;
		}
		m.i++;
	}
	return (SUCCESS);
}

t_redirection	*ft_count_simple_redirect(char *str)
{
	int i;
	char **str_2;
	int j = 0;
	t_redirection *red;
	
	str_2 = NULL;
	i = 0;
	red = malloc(sizeof(t_redirection));
	red->redirection_normal = 0;
	red->redirection_inverse = 0;
	red->double_red_norm = 0;
	red->double_red_inv = 0;
	str_2 = ft_split(str, ' ');

	if (ft_check_chev_errors(str_2) == 1)
	{
		ft_free_charr(str_2);
		return (red);
	}

	red->redirection_normal = ft_strchevroncmp(str_2, '>');
	red->redirection_inverse = ft_strchevroncmp(str_2, '<');
	red->double_red_norm = ft_strdblchevroncmp(str_2, ">>");
	red->double_red_inv = ft_strdblchevroncmp(str_2, "<<");

	/*while (str_2[i])
	{
		if ()
			red->redirection_normal++;
		//printf("str[i] = %c\n", str[i]);
		i++;
	}*/
	printf("redirection normal = %d\n", red->redirection_normal);
	ft_free_charr(str_2);
	return (red);
}

/*int	ft_check_redirect_errors(char *str)
{
	int i;

	if (str[i] == '<' && str[i + 1] == '<')
			red->double_red_inv++;
		if (str[i] == '>')
		{
			if (str[i + 1] != '>' && str[i + 1] == ' ' && str[i - 1 == ' '])
				red->redirection_normal++;
			if (str[0] == '>' && str[i] == ' ')
				red->redirection_normal++;
			if (str[i] == '>' && str[i + 1] == '\0')
				ft_putstr_fd("parse error", 2);
			if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>'
			 || str[i] == '>' && str[i - 1] == '>')
				red->redirection_normal++;

		}
		if (str[i] == '<' && str[i + 1] != '<' && str[i + 1] == ' ')
			red->redirection_inverse++;
	i = 0;
}*/