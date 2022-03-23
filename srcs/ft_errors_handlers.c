/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:04:09 by user42            #+#    #+#             */
/*   Updated: 2022/03/18 11:50:44 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
