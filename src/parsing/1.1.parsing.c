/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:29:02 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 16:50:19 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// returns copy of the input str all bytes within quotes set to 0, or NULL on failure
char	*blackout_quoted_content(char *str)
{
	char	*copy;
	char	quot_mark;
	int		i;

	copy = ft_strjoin("", str);
	quot_mark = 0;
	i = -1;
	while (copy[++i])
	{
		if (is_quote(copy[i]))
		{
			quot_mark = copy[i];
			i++;
			while (copy[i + 1] && copy[i] != quot_mark)
			{
				copy[i] = 48;
				i++;
			}
		}
	}
	return (copy);
}

// works
// checks syntax, prepares structs, kicksoff parsing on cmd line level
int	parse(char *pipeline, t_shell *minishell)
{
	char	*copy;

	copy = blackout_quoted_content(pipeline);
	if (!copy)
		return (perror("blackout_quoted_content"), FAILURE);
	if (!is_valid_syntax(copy))
		return (free(copy), FAILURE);
	prepare_parsing(copy, minishell);
	free(copy);
	if (parse_cmd_lines(pipeline, minishell->pipe_count + 1, minishell))
		return (FAILURE);
	print_list(minishell->cmd, minishell->pipe_count + 1); //just for testing - needs to go out
	return (SUCCESS);
}
