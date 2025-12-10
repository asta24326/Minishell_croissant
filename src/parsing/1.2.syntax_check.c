/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.2.syntax_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:55:55 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/10 12:18:00 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// checks whether pipe is valid (it needs at least 1 cmd or 1 redir on left side)
int	are_valid_pipes(char *copy)
{
	int	flag;

	flag = 0;
	while (*copy)
	{
		if (is_quote(*copy) || is_redir(*copy) || is_other(*copy))
			flag = 1;
		else if (*copy == 124)
		{
			if (flag == 0)
				return (false);
			flag = 0;
		}
		copy++;
	}
	return (true);
}

// works
// checks whether redirection has exactly 1 or 2 same arrows, +filename/delimiter
int	are_valid_redirs(char *copy)
{
	int		i;

	i = -1;
	while (copy[++i])
	{
		if (is_redir(copy[i]))
		{
			i++;
			if (copy[i] == copy[i - 1]) //case: double arrow
				i++;
			while (is_whitespace(copy[i]))
				i++;
			while (is_quote(copy[i])) //case:quoted filename/delimiter
				i++;
			if (!is_other(copy[i])) //MUST be other
				return (false);
		}
	}
	return (true);
}

// works
// checks whether quotes are closed
int	are_closed_quotes(char *copy)
{
	char	quot_mark;

	quot_mark = 0;
	while (*copy)
	{
		if (is_quote(*copy) & !quot_mark)
			quot_mark = *copy;
		else if (*copy == quot_mark)
			quot_mark = 0;
		copy++;
	}
	if (quot_mark == 0)
		return (true);
	return (false);
}

// works, no memory leaks
// checks overall syntax of input pipeline
int	is_valid_syntax(char *copy)
{
	if (!are_valid_pipes(copy))
		return (printf("Syntax error. Pipe(s) invalid.\n"), false);
	if (!are_valid_redirs(copy))
		return (printf("Syntax error. Redir(s) invalid.\n"), false);
	if (!are_closed_quotes(copy))
		return (printf("Syntax error. Unclosed quote(s).\n"), false);
	return (true);
}

// // only for testing--------------
// int	main(void)
// {
// 	char	*pipeline;
// 	int		i;

// 	pipeline = "''";
// 	// pipeline = "echo 'hi' hello | cat -l $USER | >> filex | j";
// 	if (!(is_valid_syntax(pipeline)))
// 		printf("non-valid syntax\n");
// 	else
// 		printf("valid syntax\n");
// }
