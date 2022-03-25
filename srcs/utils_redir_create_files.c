/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir_create_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:38:01 by user42            #+#    #+#             */
/*   Updated: 2022/03/25 19:38:14 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_pas_colle_chevron(char **str, int i)
{
	g_list->file_open = open(str[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if (g_list->file_open < 0)
		return (ft_custom_error("Error > pas colle"));
	if (dup2(g_list->file_open, STDOUT_FILENO) < 0 )
		return (ft_custom_error("Error with > for dup2"));
	return (SUCCESS);
}

int ft_pas_colle_double_chevron(char **str, int i)
{
	g_list->file_open = open(str[i + 1], O_WRONLY | O_APPEND, O_CREAT, 0755);
	if (g_list->file_open < 0)
		return (ft_custom_error("Error >> pas colle"));
	if (dup2(g_list->file_open, STDOUT_FILENO) < 0 )
		return (ft_custom_error("Error with >> for dup2"));
	return (SUCCESS);
}

int ft_pas_colle_chevron_inverse(char **str, int i)
{
	g_list->file_open = open(str[i + 1], O_RDONLY);
	if (g_list->file_open < 0)
	{
		dup2(g_list->fd_stdin, STDIN_FILENO);
		close(g_list->file_open);
		close(g_list->fd_stdin);
		printf("%s: No such file or directory\n", str[i + 1]);
		return (FAILURE);
	}
	if (dup2(g_list->file_open, STDIN_FILENO) < 0 )
		return (ft_custom_error("Error with < for dup2"));
	return (SUCCESS);
}