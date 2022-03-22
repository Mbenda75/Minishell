/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:26:11 by user42            #+#    #+#             */
/*   Updated: 2022/03/22 17:32:26 by user42           ###   ########.fr       */
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

int create_redir(char **tab, int i, t_fd fd)
{
	if (tab[i][0] == '>')
		ft_pas_colle_chevron(tab, i, fd);
	if (tab[i][0] == '>' && tab[i][1] == '>')
		ft_pas_colle_double_chevron(tab, i, fd);
	if (tab[i][0] == '<')
		ft_pas_colle_chevron_inverse(tab, i, fd);
	return (SUCCESS);
}
int	ft_heredoc(char **tab, int i)
{
	int fd[2];
	char *input;
	char *temp;
	char *ret;
	char *delimiter;

	ret = calloc(sizeof(char), 1);
	input = calloc(sizeof(char), 1);
	fd[1] = open(tab[i - 1], O_RDWR);
	if (fd[1] < 0)
		return (ft_custom_error("Error open HEREDOC"));
	if (dup2(fd[STDOUT_FILENO], STDOUT_FILENO) < 0)
		return (ft_custom_error("Error with HEREDOC for dup2"));
	signal(SIGINT, ft_signals_handler);
	delimiter = tab[i + 1];
	while (1)
	{
		input = readline("prompt>");
		add_history(input);
		if (strcmp(input, delimiter) == 0)
			break ;
		ret = ft_strjoin(ret, input);
		temp = ret;
		ret = ft_strjoin(ret, "\n");
	}
	free(temp);
	ft_putstr_fd(ret, fd[STDOUT_FILENO]);
	close(fd[STDOUT_FILENO]);
	free(input);
	free(ret);
	return (SUCCESS);
}

int	ft_check_redirection(char *str)
{
	char **tab;
	char *str_2;
	t_fd fd;
	int i;
	int j;
	
	i = 0;
	tab = NULL;
 	if (ft_check_all_redir_errors(str) == FAILURE)
		return (FAILURE);
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		j = 0;
		if (strcmp(tab[i], "<<") == 0)
			ft_heredoc(tab, i);
		if (tab[i][2] == '\0')
			create_redir(tab, i, fd);
		else 
		{
			while (tab[i][j])
			{
				open_redir(tab, i, j);
				j++;
			}
		}
		i++;
	}
	ft_free_charr(tab);
	return (SUCCESS);
}