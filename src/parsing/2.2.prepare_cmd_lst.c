/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:40:26 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 14:24:33 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// creates t_cmd node
t_cmd	*create_node(char *cmd_line)
{
	t_cmd	*new;
	char	*copy;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (perror("create_node, t_cmd"), NULL);
	copy = blackout_quoted_content(cmd_line);
	if (!copy)
		return (perror("create_node, copy"), free(new), NULL);
	if (prepare_args_arr(copy, new))//creates char **args, int args_count, int redirs_count
		return (free(new), free(copy), NULL);
	new->builtin = NULL;
	if (new->redirs_count > 0)
	{
		if (prepare_redirs(cmd_line, new))
			return (free(new), free(copy), NULL);
	}
	else
		new->redirs = NULL;
	new->next = NULL;
	return (free(copy), new);
}

// works
// adds a new node to the back of the linked list
void	add_node(t_cmd **list, t_cmd *new)
{
	t_cmd	*head;

	head = *list;
	while (head != NULL && head->next != NULL)
		head = head->next;
	head->next = new;
}

// works
void	set_index(t_cmd *stack, int cmd_count)
{
	int		i;
	t_cmd	*current;

	i = -1;
	current = stack;
	while (++i < cmd_count)
	{
		current->index = i;
		current = current->next;
	}
}

// works
void	create_cmd_list(char **arr, int cmd_count, t_shell *minishell)
{
	t_cmd	*list;
	int		i;

	list = create_node(arr[0]);//initiates the list, creates first node
	i = 0;
	while (++i < cmd_count) //creates entire list by passing 1 cmd-line per node
		add_node(&list, create_node(arr[i]));
	set_index(list, cmd_count);
	minishell->cmd = list;
}
