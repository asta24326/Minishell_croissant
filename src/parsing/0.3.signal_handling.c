/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.3.signal_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:18:03 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/12 11:49:08 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// to be tested
// handles ctrl c in child process and heredoc
void	handle_signal_child(int signum)
{
	(void)signum;
	printf("\n");
	exit(130);
}

// works
// handles ctrl c in parent process (displays a new prompt on a new line)
void	handle_signal_parent(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();//updates about jump to next line
	rl_replace_line("", 0);//clears current buffer
	rl_redisplay();//refreshes readline prompt
	return ;
}

void	setup_signals(void (*signal_handler)(int))
{
	signal(SIGINT, handle_signal); //case: ctrl-C
	signal(SIGQUIT, SIG_IGN); //case: ctrl-\ - is ignored
}
