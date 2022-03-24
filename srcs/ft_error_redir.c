/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:26:11 by user42            #+#    #+#             */
/*   Updated: 2022/03/24 23:14:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_colle_chevron_inverse(char *split_by_spa)
{
	int i;
	int file_open;

	i = 0;
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
	str = ft_strtrim(str, ">");
	file_open = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0755 );
	if (file_open < 0)
	{
		free(str);
		return (ft_custom_error("Error > chevron"));
	}
	close (file_open);
	free(str);
	return (SUCCESS);
}

int ft_colle_double_chevron_normal(char *str)
{
	int i;
	int file_open;

	i = 0;
	str = ft_strtrim(str, ">>");
	file_open = open(str, O_WRONLY | O_APPEND | O_CREAT, 0755 );
	if (file_open < 0)
	{
		free(str);
		return (ft_custom_error("Error > chevron"));
	}
	close (file_open);
	free(str);
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
}

int	ft_heredoc(char **tab, int i)
{
	char *input;
	char *temp;
	char *ret;
	char *delimiter;

	//signal(SIGINT, ft_signals_handler);
	//signal(SIGINT, ft_signals_handler);

	ret = ft_calloc(sizeof(char), 1);
	delimiter = tab[i + 1];
	if (dup2(g_list->file_open, STDIN_FILENO) < 0 )
		return (FAILURE);	
	while (1)
	{
		input = readline("prompt>");
		add_history(input);
		if (strcmp(input, delimiter) == SUCCESS)
		{
			printf("JE SUIS LA\n");
			free(input);
			break ;
		}
		temp = ret;
		ret = ft_strjoin(ret, input);
		free(input);
		free(temp);
		temp = ret;
		ret = ft_strjoin(ret, "\n");
		free(temp);
	}
	free(ret);
	return (SUCCESS);
}

int	ft_check_redirection(char *str)
{
	char **tab;
	char *str_2;
	int i;
	
	i = 0;
	tab = NULL;
 	if (ft_check_all_redir_errors(str) == FAILURE)
	{
		printf("FAILURE\n");
		return (FAILURE);
	}
	tab = ft_split(str, ' ');
	g_list->fd_stdout = dup(STDOUT_FILENO);
	g_list->fd_stdin = dup(STDIN_FILENO);
	g_list->check_stds = 1;
	printf("OUT %d IN %d\n",g_list->fd_stdout, g_list->fd_stdin);
	while (tab[i])
	{
		if (strcmp(tab[i], "<<") == 0)
		{
			ft_heredoc(tab, i);
			i++;
		}
		if (tab[i][0] == '>')
			ft_pas_colle_chevron(tab, i);
		if (tab[i][0] == '>' && tab[i][1] == '>')
			ft_pas_colle_double_chevron(tab, i);
		if (tab[i][0] == '<')
			ft_pas_colle_chevron_inverse(tab, i);
		i++;
	}
	printf("JE SORS DE FT_ERROR_REDIR\n");
	//printf("file open == %d\n", g_list->file_open);
	free_str(tab);
	return (SUCCESS);
}