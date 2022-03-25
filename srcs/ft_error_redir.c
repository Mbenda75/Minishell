/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:26:11 by user42            #+#    #+#             */
/*   Updated: 2022/03/25 18:03:27 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_colle_chevron_inverse(char *split_by_spa)
{
	int file_open;

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
	int file_open;

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
	int file_open;

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

/*char *ft_heredoc(char **tab, int i)
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
		//temp = ret;
		//ret = ft_strjoin(ret, "\n");
		//free(temp);
	}
	printf("ret = %s", ret);
	//free(ret);
	return (ret);
}*/

int	ft_check_redirection(char *str)
{
 	if (ft_check_all_redir_errors(str) == FAILURE)
	{
		printf("FAILURE\n");
		return (FAILURE);
	}
	return (SUCCESS);
}