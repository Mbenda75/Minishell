/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:45:36 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/25 16:08:16 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_heredoc(char **tab, int i)
{
	char *input;
	char *temp;
	char *ret;
	char *delimiter;

	ret = ft_calloc(sizeof(char), 1);
	delimiter = tab[i + 1];
	while (1)
	{
		input = readline(">");
		add_history(input);
		if (strcmp(input, delimiter) == SUCCESS)
		{
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
	printf("ret = %s\n", ret);
	free(ret);
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
		if (strcmp(tab[i], "<<") == 0)
			ft_heredoc(tab, i);
		if (tab[i][0] == '>')
			ft_pas_colle_chevron(tab, i);
		if (tab[i][0] == '>' && tab[i][1] == '>')
			ft_pas_colle_double_chevron(tab, i);
		if (tab[i][0] == '<')
			ft_pas_colle_chevron_inverse(tab, i);	
		i++;
	}
	free_str(tab);
	return (SUCCESS);
}