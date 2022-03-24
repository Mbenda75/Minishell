/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:45:36 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/24 17:14:11 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*int	ft_heredoc(char **tab, int i)
{
	char *input;
	char *temp;
	char *ret;
	char *delimiter;

	ret = ft_calloc(sizeof(char), 1);
	delimiter = tab[i + 1];
	while (1)
	{
		input = readline("prompt>");
		add_history(input);
		if (strcmp(input, delimiter) == 0 || signal(SIGINT, ft_signals_handler))
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
	ft_putstr_fd(ret, STDOUT_FILENO);
	free(ret);
	return (SUCCESS);
}


int ft_redir_handler(char *str)
{
    int i;
    char **tab;
    
    i = 0;
	tab = ft_split(str, ' ');
	g_list->fd_stdout = dup(STDOUT_FILENO);
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
	free_str(tab);
}*/
