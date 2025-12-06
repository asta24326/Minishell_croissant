/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.2.syntax_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:55:55 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/04 18:33:39 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// checks whether redirection has correct syntax
// takes the current byte which is a redir sign
// attention: I do not handle non-closed quotes (as discussed)
int	is_valid_redir(char *str)
{
	char	redir_sign;
	char	quot_mark;

	redir_sign = *str;
	str++;
	// ensures that directly following byte is the same (if there is one)
	if (*str == 60 || *str == 62)
	{
		if (*str != redir_sign)
			return (ft_printf("Syntax error. Mixed redir signs."), 0);
		str++;
	}
	// loops through whitespaces if needed
	while (is_whitespace(*str))
		str++;
	// ensures a valid filename or delimiter is linked to redir sign
	// ensures the amount of redir sign does not exceed 2 in a row
	if (is_token(*str) || *str == 45 || !*str)
		return (ft_printf("Syntax error. No filename/delimiter."), 0);
	// ensures quotes are non-empty
	else if (is_quote(*str))
	{
		quot_mark = *str;
		str++;
		if (*str == quot_mark)
			return (ft_printf("Syntax error. No filename/delimiter."), 0);
	}
	return (1);
}

// works
// checks whether pipe is valid (it needs at least 1 cmd or 1 redir on left side)
// loops through entire input str
int	are_valid_pipes(char *str)
{
	int		flag_cmd;
	int		flag_redir;

	flag_cmd = 0;
	flag_redir = 0;
	while (*str)
	{
		if (!(is_whitespace(*str)) && !(is_token(*str)) && !(is_prefix(*str))
			&& flag_cmd == 0)
			flag_cmd = 1;
		if (*str == 60 || *str == 62)
			flag_redir = 1;
		if (*str == 124 || !*str)
		{
			if (flag_cmd == 0 && flag_redir == 0)
				return (printf("Syntax error. Missing command/redir.\n"), 0);
			if (*str == 124)
				flag_cmd = 0;
		}
		str++;
	}
	return (1);
}

// works, no memory leaks
// checks overall syntax of input str
// attention: I do not handle non-closed quotes (as discussed)
int	is_valid_syntax(char *str)
{
	char	*copy;
	int		i;

	copy = blackout_quoted_content(str);
	if (!(are_valid_pipes(copy)))
		return (printf("Syntax error. Pipe(s) invalid.\n"), 0);
	i = 0;
	while (copy[i])
	{
		//check redirections 1 by 1
		if (copy[i] == 60 || copy[i] == 62)
		{
			if (!(is_valid_redir(copy + i)))
				return (printf("Syntax error. Redir(s) invalid.\n"), 0);
		}
		i++;
	}
	free(copy);
	return (1);
}

// // only for testing--------------
// int	main(void)
// {
// 	char	*str;
// 	int		i;

// 	str = "''";
// 	// str = "echo 'hi' hello | cat -l $USER | >> filex | j";
// 	if (!(is_valid_syntax(str)))
// 		printf("non-valid syntax\n");
// 	else
// 		printf("valid syntax\n");
// }
