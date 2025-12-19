/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:56:50 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 17:52:54 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// returns amout of heredocs within 1 cmd line
int	get_hdoc_count(char *copy)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (copy[++i])
		if (copy[i] == '<' && copy[i + 1] == '<')
			count += 1;
	return (count);
}

// works
// sets up t_redirs
int	prepare_redirs(char *copy, t_cmd *cmd)
{
	t_redirs	*redirects;

	redirects = (t_redirs *)malloc(sizeof(t_redirs));
	if (!redirects)
		return (perror("prepare_redirs, struct"), FAILURE);
	redirects->list = ft_calloc(cmd->redirs_count + 1, sizeof(char *));
	if (!redirects->list)
		return (perror("prepare_redirs, list"), free(redirects), FAILURE);
	redirects->in_fd = 0;
	redirects->out_fd = 0;
	// redirects->append_fd = 0;
	redirects->hdoc_count = get_hdoc_count(copy); //needed? check how often used in the end //RAUS bitte, sonst error handling
	redirects->hdoc_delim = NULL;
	redirects->exp_hdoc = true; //needed? rather NO
	cmd->redirs = redirects;
	return (SUCCESS);
}
