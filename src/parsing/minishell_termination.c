/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_termination.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:28:14 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 11:07:57 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end_minishell(t_shell *minishell)
{
	free(minishell->prompt);
	ft_free_arr(minishell->env);
	free(minishell);
	minishell = NULL;
	rl_clear_history();
}
