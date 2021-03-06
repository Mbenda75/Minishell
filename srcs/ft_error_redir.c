/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:26:11 by user42            #+#    #+#             */
/*   Updated: 2022/03/27 23:06:45 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_redirection(char *str)
{
	if (ft_check_all_redir_errors(str) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
