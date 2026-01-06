/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.2.minishell_initialization.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:13:31 by kschmitt          #+#    #+#             */
/*   Updated: 2026/01/06 13:54:00 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_minishell(t_shell *minishell)
{
	minishell->prompt = ft_strjoin(getenv("USER"), "@croissant_minishell: ");
	if (!minishell->prompt)
		return (FAILURE);
	minishell->pipe_count = 0;
	minishell->pipes = NULL;
	minishell->cmd = NULL;
	minishell->exit_status = 0;
	minishell->shell_pid = getpid();
	minishell->orig_stdin = dup(STDIN_FILENO);
	minishell->orig_stdout = dup(STDOUT_FILENO);
	ft_setup_signals();
	return (SUCCESS);
}
