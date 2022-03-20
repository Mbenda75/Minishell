/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:04:09 by user42            #+#    #+#             */
/*   Updated: 2022/03/20 02:02:59 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_free_charr(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_system_error(void)
{
	int	errnum;

	errnum = errno;
	printf("mnsh: %s\n", strerror(errnum));
	return (FAILURE);
}

int	ft_custom_error(char *errstr)
{
	printf("minishell: %s\n", errstr);
	return (FAILURE);
}
