/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.6.create_cmd_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:40:26 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/01 17:42:56 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// what I do here:
// - split the pipeline into array of command
// - needed: number of commands
// - needed for each str: str_len

typedef struct	s_cmd
{
//	char			*name - no need anymore
	char			**args;
	char			*hdoc_delim;
	bool			closed; // false if further input is needed through interaction
	bool			builtin;// true if is builtin command
	t_redirs		*redirs;
	struct t_cmd	*next;
}	t_cmd;
