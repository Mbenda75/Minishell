/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:45:36 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/28 00:14:23 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_heredoc_fd(void)
{
	g_list->hrdc_stdout = open("temp", O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if (g_list->hrdc_stdout < 0)
		return (ft_custom_error("Error <<"));
	return (SUCCESS);
}

int	ft_heredoc_write_and_dup(void)
{
	write(g_list->hrdc_stdout, g_list->r_hdc, ft_strlen(g_list->r_hdc) + 1);
	g_list->hrdc_stdin = open("temp", O_RDONLY);
	if (g_list->hrdc_stdin < 0)
		return (ft_custom_error("Error << dup2 open"));
	if (dup2(g_list->hrdc_stdin, STDIN_FILENO) < 0)
		return (ft_custom_error("Error << dup2 open"));
	return (SUCCESS);
}

int	ft_heredoc(char **tab, int i)
{
	char	*input;
	char	*temp;
	char	*delimiter;

	g_list->r_hdc = ft_calloc(sizeof(char), 1);
	delimiter = tab[i + 1];
	if (ft_heredoc_fd() == FAILURE)
		return (FAILURE);
	while (1)
	{
		input = readline(">");
		if (strcmp(input, delimiter) == SUCCESS)
			break ;
		temp = g_list->r_hdc;
		g_list->r_hdc = ft_strjoin(g_list->r_hdc, input);
		free(input);
		free(temp);
		temp = g_list->r_hdc;
		g_list->r_hdc = ft_strjoin(g_list->r_hdc, "\n");
		free(temp);
	}
	free(input);
	if (ft_heredoc_write_and_dup() == SUCCESS)
		return (SUCCESS);
	return (SUCCESS);
}

int	ft_redir_handler(char *str)
{
	int			i;
	char		**tab;

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
	free_str(tab);
	return (SUCCESS);
}
