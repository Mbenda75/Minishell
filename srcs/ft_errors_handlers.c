/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:04:09 by user42            #+#    #+#             */
/*   Updated: 2022/02/21 15:10:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_charr(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

int	ft_system_error(void)
{
	int	errnum;
	int	fout;

	fout = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	errnum = errno;
	printf("mnsh: %s\n", strerror(errnum));
	dup2(fout, STDOUT_FILENO);
	close(fout);
	return (FAILURE);
}

int	ft_custom_error(char *errstr)
{
	int	fout;

	fout = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("minishell: %s\n", errstr);
	dup2(fout, STDOUT_FILENO);
	close(fout);
	return (FAILURE);
}
