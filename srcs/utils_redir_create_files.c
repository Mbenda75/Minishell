/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir_create_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:38:01 by user42            #+#    #+#             */
/*   Updated: 2022/03/22 17:23:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_pas_colle_chevron(char **str, int i, t_fd fd)
{
	int file_open;

	file_open = open(str[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if (file_open < 0)
		return (ft_custom_error("Error > pas colle"));
	if (dup2(file_open, STDOUT_FILENO) < 0 )
		return (ft_custom_error("Error with > for dup2"));
	close (file_open);
	return (SUCCESS);
}

int ft_pas_colle_double_chevron(char **str, int i, t_fd fd)
{
	int file_open;

	file_open = open(str[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0755);
	if (file_open < 0)
		return (ft_custom_error("Error >> pas colle"));
	if (dup2(file_open, STDOUT_FILENO) < 0 )
		return (ft_custom_error("Error with >> for dup2"));
	close (file_open);
	return (SUCCESS);
}

int ft_pas_colle_chevron_inverse(char **str, int i, t_fd fd)
{
	int file_open;

	file_open = open(str[i + 1], O_RDONLY);
	if (file_open < 0)
	{
		printf("No such file or directory %s\n", str[i]);
		return (FAILURE);
	}
	if (dup2(file_open, STDIN_FILENO) < 0 )
		return (ft_custom_error("Error with < for dup2"));
	close (file_open);
	return (SUCCESS);
}