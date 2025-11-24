/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.2.ctrl_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:39:01 by kschmitt          #+#    #+#             */
/*   Updated: 2025/11/24 17:42:09 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// --------------WIP-----------------
// void	disable_echo(void)
// {
// 	struct termios	w_echo;
// 	struct termios	wo_echo;

// 	tcgetattr(STDIN_FILENO, TCSAFLUSH, &w_echo);

// }

// handles 'ctrl-c' && 'ctrl-\'
void	handle_signal(int signum)
{
	// 'ctrl-c': displays a new prompt on command line
	if (signum == 2)
		printf("\n");
	// 'ctrl-\': does nothing - so, does ignore SIGQUIT, disbales echo (nothing to be seen)
	if (signum == 3)
	{
		printf(" - ignoring!\n");		//needs to be handled!
		disable_echo();
	}
	return ;
}

// endless loop, waiting for keyhooks
// handles 'ctrl-d'
int	main(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		// 'ctrl-d': exits the shell, after printing "exit"
		if (getchar() == EOF)			//attention: getchar() not allowed
		{
			printf("exit\n");
			exit(1);
		}
		pause();
	}
	return (0);
}
