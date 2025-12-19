/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:49:19 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 15:14:51 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// returns length of cmd/flag/arg/env_arg
int	get_arg_len(char *str)
{
	int		len;
	char	quot_mark;

	len = 0;
	while (str[len] && !is_whitespace(str[len]) && !is_operator(str[len]))
	{
		if (is_quote(str[len]))
		{
			quot_mark = str[len];
			len += 1;
			while (str[len] && str[len] != quot_mark)
				len += 1;
			len += 1;
		}
		else if (is_other(str[len]))
		{
			while (str[len] && !is_whitespace(str[len])
				&& !is_operator(str[len]) && !is_quote(str[len]))
				len += 1;
		}
	}
	return (len);
}

// works
// includes the cmd/flag/arg/env_arg into the args_array
// attention, this will be called repeatedly as soon as arg is encountered
void	fill_args_arr(char *arg, t_cmd *cmd)
{
	static int	i; // needed because of repeated call

	cmd->args[i] = arg;
	i++;
	if (i == cmd->args_count) // NULL-terminate array and reset i to 0 when all cmds were handled
	{
		cmd->args[i] = NULL;
		i = 0;
	}
}

// works
// loops through cmd/flag/arg/env_arg and returns index after last byte
int	parse_cmd(char *cmd_str, t_cmd *cmd)
{
	int		index;
	char	*arg;

	index = get_arg_len(cmd_str);
	arg = ft_substr(cmd_str, 0, index);
	if (!arg)
		return (perror("parse_cmd"), -1);
	fill_args_arr(arg, cmd);
	return (index);
}
