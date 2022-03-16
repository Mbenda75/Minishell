/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:26:11 by user42            #+#    #+#             */
/*   Updated: 2022/03/15 19:30:16 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_get_next_chevron(char **str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if ((ft_strcmp(str[i], ">") == 0 && ft_strcmp(str[i + 1], ">") == 0) ||
			(ft_strcmp(str[i], ">") == 0 && ft_strcmp(str[i + 1], "<") == 0) ||
			(ft_strcmp(str[i], ">") == 0 && ft_strcmp(str[i + 1], "<<") == 0) ||
			(ft_strcmp(str[i], ">") == 0 && ft_strcmp(str[i + 1], ">>") == 0) ||
			(ft_strcmp(str[i], "<") == 0 && ft_strcmp(str[i + 1], "<") == 0) ||
			(ft_strcmp(str[i], "<") == 0 && ft_strcmp(str[i + 1], ">") == 0) ||
			(ft_strcmp(str[i], "<") == 0 && ft_strcmp(str[i + 1], "<<") == 0) ||
			(ft_strcmp(str[i], "<") == 0 && ft_strcmp(str[i + 1], ">>") == 0) ||
			(ft_strcmp(str[i], ">>") == 0 && ft_strcmp(str[i + 1], ">") == 0) ||
			(ft_strcmp(str[i], ">>") == 0 && ft_strcmp(str[i + 1], "<") == 0) ||
			(ft_strcmp(str[i], ">>") == 0 && ft_strcmp(str[i + 1], "<<") == 0) ||
			(ft_strcmp(str[i], ">>") == 0 && ft_strcmp(str[i + 1], ">>") == 0) ||
			(ft_strcmp(str[i], "<<") == 0 && ft_strcmp(str[i + 1], ">") == 0) ||
			(ft_strcmp(str[i], "<<") == 0 && ft_strcmp(str[i + 1], "<") == 0) ||
			(ft_strcmp(str[i], "<<") == 0 && ft_strcmp(str[i + 1], "<<") == 0) ||
			(ft_strcmp(str[i], "<<") == 0 && ft_strcmp(str[i + 1], ">>") == 0))
			{
				printf("ECHEC JE SUIS LA --> NEXT_CHEVRON 1\n");
				return (FAILURE);
			}
	}
	printf("REUSSITE JE SUIS LA --> NEXT_CHEVRON 1\n");
	return (SUCCESS);
}

int ft_check_get_next_chevron_2(char **str)
{
	int i;
	int j;

	i = -1;
	while (str[++i])
	{
		if ((ft_strcmp(str[i], ">") == 0 && str[i + 1][0] == '>') ||
			(ft_strcmp(str[i], ">") == 0 && str[i + 1][0] == '<') ||
			(ft_strcmp(str[i], ">") == 0 && str[i + 1][0] == '<' && str[i + 1][1] == '<') ||
			(ft_strcmp(str[i], ">") == 0 && str[i + 1][0] == '>' && str[i + 1][1] == '>') ||
			(ft_strcmp(str[i], "<") == 0 && str[i + 1][0] == '<') ||
			(ft_strcmp(str[i], "<") == 0 && str[i + 1][0] == '>') ||
			(ft_strcmp(str[i], "<") == 0 && str[i + 1][0] ==  '<' && str[i + 1][1] == '<') ||
			(ft_strcmp(str[i], "<") == 0 && str[i + 1][0] == '>' && str[i + 1][1] == '>') ||
			(ft_strcmp(str[i], ">>") == 0 && str[i + 1][0] == '>') ||
			(ft_strcmp(str[i], ">>") == 0 && str[i + 1][0] == '<') ||
			(ft_strcmp(str[i], ">>") == 0 && str[i + 1][0] == '<' && str[i + 1][1] == '<') ||
			(ft_strcmp(str[i], ">>") == 0 && str[i + 1][0] == '>' && str[i + 1][1] == '>') ||
			(ft_strcmp(str[i], "<<") == 0 && str[i + 1][0] == '>') ||
			(ft_strcmp(str[i], "<<") == 0 && str[i + 1][0] == '<') ||
			(ft_strcmp(str[i], "<<") == 0 && str[i + 1][0] == '<' && str[i + 1][1] == '<') ||
			(ft_strcmp(str[i], "<<") == 0 && str[i + 1][0] == '>' && str[i + 1][1] == '>'))
			{
				printf("ECHEC JE SUIS LA --> CHEVRON 2\n");
				return (FAILURE);
			}
	}
	printf("REUSSITE JE SUIS LA --> CHEVRON 2\n");
	return (SUCCESS);
}

int ft_check_chev_errors(char **str)
{
	t_decompte k;

	k.i = -1;
	k.j = 0;
	while (str[k.j])
		k.j++;
	if (ft_strcmp(str[k.j - 1], ">") == 0 || ft_strcmp(str[k.j - 1], "<") == 0 ||
		ft_strcmp(str[k.j - 1], ">>") == 0 || ft_strcmp(str[k.j - 1], "<<") == 0)
			return (ft_custom_error("ERROR POUR CHEVRON A LA FIN DE STR syntax error near unexpected token 'newline'"));
	k.j = k.j - 1;
	if (ft_strcmp(str[0], "<") == 0 || ft_strcmp(str[0], "<<") == 0)
		return (ft_custom_error("ERROR POUR CHEVRON AU DEBUT DE STR No such file or directory"));
	if (ft_check_get_next_chevron(str) == 1)
		return (ft_custom_error("CHEVRON 1 syntax error near unexpected token"));
	if (ft_check_get_next_chevron_2(str) == 1)
		return (ft_custom_error("CHEVRON 2syntax error near unexpected token"));
	while (str[++k.i] && k.i <= k.j)
	{
		if (ft_strcmp(str[k.i], ">") == 0 || (ft_strcmp(str[k.i], ">>") == 0 ||
			ft_strcmp(str[k.i], "<") == 0 || ft_strcmp(str[k.i], "<<") == 0))
			{
				printf("SUCCESS -> AUCUNE ERREUR TROUVEE\n");
				return (SUCCESS);
			}
	}
	return (ft_custom_error("ERROR FIN DE CYCLE syntax error near unexpected token"));
}

int ft_create_file(char **str)
{
	int fd_in;
	int fd_out;
	int fd_err;
	int i;
	int file_open;

	fd_in = dup(0);
	fd_out = dup(1);
	fd_err = dup(2);
	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], ">") == 0)
		{
			file_open = open(str[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0755 );
			if (file_open < 0)
				return (ft_custom_error("Error > chevron"));
			if (dup2(file_open, 0) < 0)
				return (ft_custom_error("Error > chevron"));
			close (file_open);
			str[i] = NULL;
			str[i + 1] == NULL;
			i = i + 2;
		}
		else if (ft_strcmp(str[i], ">>") == 0)
		{
			file_open = open(str[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0755 );
			if (file_open < 0)
				return (ft_custom_error("Error >> chevron"));
			if (dup2(file_open, 0) < 0)
				return (ft_custom_error("Error >> chevron"));
			close (file_open);
			str[i] = NULL;
			str[i + 1] == NULL;
			i = i + 2;
		}
		i++;
	}
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	dup2(fd_err, 2);
}

t_redir	*ft_count_simple_redirect(char *str)
{
	int i;
	char **str_2;
	int j = 0;
	t_redir *red;
	
	str_2 = NULL;
	i = 0;
	red = malloc(sizeof(t_redir));
	red->redirection_normal = 0;
	red->redirection_inverse = 0;
	red->double_red_norm = 0;
	red->double_red_inv = 0;
	str_2 = ft_split(str, ' ');
	printf("JE SUIS ICI\n");
 	if (ft_check_chev_errors(str_2) == 1)
	{
		printf("ERROR\n");
		ft_free_charr(str_2);
		return (red);
	} 
	printf("REUSSITE\n");
	ft_create_file(str_2);
	//printf("redirection normal = %d\n", red->redirection_normal);
	ft_free_charr(str_2);
	return (red);
}