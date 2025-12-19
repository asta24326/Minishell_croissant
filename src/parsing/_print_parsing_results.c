/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _print_parsing_results.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@dent.42berlin.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:32:56 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/19 14:06:44 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// goes out - only for testing
void	print_list(t_cmd *cmd, int cmd_count)
{
	int		i;
	int		j;
	t_cmd	*current;

	i = 0;
	current = cmd;

	printf("#cmd: %i\n", cmd_count);
	while (i < cmd_count)
	{
		j = -1;
		printf("------------- ARG %i -----------\n", i);
		printf("index: %i\n", current->index);
		printf("args: ");
		while (current->args[++j])
			printf("[%s] ", current->args[j]);
		printf("\n");
		printf("is builtin: %i\n\n", current->builtin);
		if (current->redirs != 0)
		{
			printf("   ---- REDIR IN ARG %i ----\n", i);
			printf("   in_fd: %i\n", current->redirs->in_fd);
			printf("   out_fd: %i\n", current->redirs->out_fd);
			printf("   hdoc_delim: [%s]\n", current->redirs->hdoc_delim);
			printf("   exp_hdoc: %i\n", current->redirs->exp_hdoc);
		}
		printf("\n\n\n");
		//start
		//attention, this is only relevant if parsing is tested without execution
		//please mute in case of testing in combination with exec, as fds are closed there already
		if (current->redirs->in_fd != 0)
			close(current->redirs->in_fd);
		if (current->redirs->out_fd != 0)
			close(current->redirs->out_fd);
		//end
		current = current->next;
		i++;
	}
	printf("--------------------------------\n");
}
