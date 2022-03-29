/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 22:29:25 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/27 22:48:11 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_all_redir_errors_norm(char *str)
{
	if (ft_check_chevron_grammar_1(str) == FAILURE)
		return (FAILURE);
	if (ft_check_chevron_grammar_2(str) == FAILURE)
		return (FAILURE);
	if (ft_check_space_at_the_end(str) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_check_all_redir_errors(char *str)
{
	if (ft_check_all_redir_errors_norm(str) == FAILURE)
		return (FAILURE);
	if (strchr(str, '<'))
	{
		if (ft_check_file_existence(str) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
