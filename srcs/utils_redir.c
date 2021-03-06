/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:27:19 by user42            #+#    #+#             */
/*   Updated: 2022/03/27 22:31:22 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_if_no_redir(char *str)
{
	int	i;

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

int	ft_check_chevron_grammar_1(char *str)
{
	int	i;
	int	check;

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

int	ft_check_chevron_grammar_2(char *str)
{
	int	i;
	int	check;

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

int	ft_check_space_at_the_end(char *str)
{
	int		i;
	char	*error_str;

	error_str = "syntax error near unexpected token newline";
	i = ft_strlen(str) - 1;
	if (str[i] == '<' || str[i] == '>')
		return (ft_custom_error(error_str));
	if (str[i] == ' ')
	{
		while (str[i] == ' ')
			i--;
		if (str[i] == '>' || str[i] == '<')
			return (ft_custom_error(error_str));
	}
	return (SUCCESS);
}

int	ft_check_file_existence(char *str)
{
	t_decompte	index;
	char		**split_byspace;

	index.i = -1;
	split_byspace = ft_split(str, ' ');
	while (split_byspace[++index.i])
	{
		if (split_byspace[index.i][0] == '<'
		&& split_byspace[index.i][1] != '<')
		{
			index.j = open(split_byspace[index.i + 1], O_RDONLY);
			if (index.j < 0)
			{
				close(index.j);
				printf("%s: No such file or directory\n",
					split_byspace[index.i + 1]);
				free_str(split_byspace);
				return (FAILURE);
			}
		}
	}
	free_str(split_byspace);
	close(index.j);
	return (SUCCESS);
}
