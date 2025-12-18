/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initialization.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:13:31 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 11:28:30 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// sets the prompt, reads the user input and saves it into a char *buffer
// program loop with signal handling
// creates and continously adds to history if input is non-empty
int	init_minishell(t_shell *minishell)
{
	char	*input_str;

	minishell->prompt = ft_strjoin(getenv("USER"), "@minishell: ");
	setup_signals(handle_signal_parent);
	while (1)
	{
		input_str = readline(minishell->prompt);
		if (!input_str)// exits in case of ctrl-D
		{
			printf("exit\n");
			exit(1);
		}
		if (*input_str)
		{
			if (parse_pipeline(input_str, minishell))
			{
				free(input_str);
				exit(1);
			}
			// execute(minishell);
			add_history(input_str); //adds user input to history
			free(input_str);
		}
	}
	return (0);
}
