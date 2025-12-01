/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.3.parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:18:34 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/01 17:36:07 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// takes the current byte at which we stopped and looks into the following one(s)
// returns the next non-whitespace character
// does not change the pointer position of source str
char	sneak_preview(char *str)
{
	printf("arrived: %s\n", str);
	while (*str)
	{
		str++;
		if (!(is_whitespace(*str)))
			return (*str);
	}
	return (0);
}


int	parse(char *pipeline, char **env)
{
	int	i;

	i = 0;
	//syntax_check
	if (!is_valid_syntax(pipeline))
		return (printf("Syntax error.\n"), FAILURE);
	//extract data for t_shell
	if (!parse_pipeline(pipeline, env))
		return (printf("Error while extracting t_shell data.\n"), FAILURE);
// I AM HERE >> from here I continue in parse_pipeline
	while (pipeline[i])
	{
		if (pipeline[i] == 60 || pipeline[i] == 62)
			parse_redir(pipeline + i);				//attention, I need to get back the byte after redir

		i++;
	}
	//list_creation
	//parsing
	return (SUCCESS);
}
