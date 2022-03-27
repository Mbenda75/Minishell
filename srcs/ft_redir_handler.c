/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:45:36 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/27 20:35:04 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_heredoc(char **tab, int i)
{
	char *input;
	char *temp;
	char *delimiter;

	g_list->ret_herdc = ft_calloc(sizeof(char), 1);
	delimiter = tab[i + 1];
	g_list->hrdc_STDOUT = open("temp", O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if (g_list->hrdc_STDOUT < 0)
		return (ft_custom_error("Error <<"));
	while (1)
	{
		input = readline(">");
		add_history(input);
		if (strcmp(input, delimiter) == SUCCESS)
		{
			free(input);
			break ;
		}
		temp = g_list->ret_herdc;
		g_list->ret_herdc = ft_strjoin(g_list->ret_herdc, input);
		free(input);
		free(temp);
		temp = g_list->ret_herdc;
		g_list->ret_herdc = ft_strjoin(g_list->ret_herdc, "\n");
		free(temp);
	}
	write(g_list->hrdc_STDOUT, g_list->ret_herdc, ft_strlen(g_list->ret_herdc) + 1);
	g_list->hrdc_STDIN = open("temp", O_RDONLY);
	if (g_list->hrdc_STDIN < 0)
		return (ft_custom_error("Error << dup2 open"));
	if (dup2(g_list->hrdc_STDIN, STDIN_FILENO) < 0)
		return (ft_custom_error("Error << dup2 open"));
	return (SUCCESS);
}

int ft_redir_handler(char *str)
{
    int i;
    char **tab;
	
	i = 0;
	tab = ft_split(str, ' ');
	g_list->fd_stdout = dup(STDOUT_FILENO);
	g_list->fd_stdin = dup(STDIN_FILENO);
	g_list->check_stds = 1;
	while (tab[i])
	{
		if (tab[i][0] == '>' && tab[i][1] != '>')
			ft_pas_colle_chevron(tab, i);
		if (tab[i][0] == '>' && tab[i][1] == '>')
			ft_pas_colle_double_chevron(tab, i);
		if (tab[i][0] == '<' && tab[i][1] != '<')
			ft_pas_colle_chevron_inverse(tab, i);	
		if (tab[i][0] == '<' && tab[i][1] == '<')
			ft_heredoc(tab, i);
		i++;
	}
	printf("SORTI DU ft_redir_handler\n");
	free_str(tab);
	return (SUCCESS);
}
