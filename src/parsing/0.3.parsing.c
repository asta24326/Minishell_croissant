/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.3.parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:18:34 by kschmitt          #+#    #+#             */
/*   Updated: 2025/11/27 20:05:54 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// checks whether c is space or horizontal tab
// attention: without '\n'
int	is_whitespace(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

// checks whether c is pipe, right or left arrow
int	is_token(char c)
{
	if (c == 124 || c == 60 || c == 62)
		return (1);
	return (0);
}

// checks whether c is double or single quotation mark
int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

// checks whether c is '$' (prefix for env. arg.) or '-' (prefix for flag)
int	is_prefix(char c)
{
	if (c == 36 || c == 45)
		return (1);
	return (0);
}

// TO BE REDONE! >> all passed by struct
// checks whether cmd is built-in command
// sends it directly to execution (except for echo and cd)
int	is_builtin_cmd(char *str)
{
	// returns 2 (as flag if you want) to indicate that those commands will be passed through struct
	if (!(ft_strncmp(str, "echo", ft_strlen(str)))
		|| !(ft_strncmp(str, "cd", ft_strlen(str))))
		return (2);
	else if (!(ft_strncmp(str, "pwd", ft_strlen(str))))
		exec_pwd();
	else if (!(ft_strncmp(str, "export", ft_strlen(str))))
		exec_export();
	else if (!(ft_strncmp(str, "unset", ft_strlen(str))))
		exec_unset();
	else if (!(ft_strncmp(str, "env", ft_strlen(str))))
		exec_env();
	else if (!(ft_strncmp(str, "exit", ft_strlen(str))))
		exec_exit();
	else
		return (0);
	return (1);
}

// checks whether redirection has correct syntax
// attention: I do not handle non-closed quotes (as discussed)
// has to be checked before: token is not quoted
int	is_valid_redir(char *str)
{
	int		count;
	char	quot_mark;

	count = 0;
	while (*str)
	{
		// loops through redir sign(s)
		while (*str == 60 || *str == 62)
		{
			count++;
			str++;
			// ensures the amount of redir sign does not exceed 2 in a row
			if (count > 2)
				return (ft_printf("Syntax error. Too many redir signs."), 1);
		}
		// loops through whitespaces if needed
		while (is_whitespace(*str))
			str++;
		// ensures a valid filename or delimiter is linked to redir sign
		if (is_token(*str) || *str == 45 | !*str)
			return (ft_printf("Syntax error. No filename/delimiter."), 1);
		// ensures quotes are non-empty
		else if (is_quote(*str))
		{
			quot_mark = *str;
			str++;
			if (*str == quot_mark)
				return (ft_printf("Syntax error. No filename/delimiter."), 1);
		}
		break ;
	}
	return (0);
}

// checks whether syntax is correct
// attention: I do not handle non-closed quotes (as discussed)
int	is_valid_syntax(char *str)
{
	int		flag_cmd;
	char	quot_mark;

	flag_cmd = 0;
	quot_mark = 0;
	while (*str)
	{
		// loop through whitespaces
		while (is_whitespace(*str))
			str++;
		// case: cmd is not in quotes
		if (!(is_token(*str)) && !(is_prefix(*str)) && !(is_quote(*str))
			&& flag_cmd == 0)
		{
			flag_cmd = 1;
			while (!(is_whitespace(*str)) && !(is_token(*str)))
				str++;
		}
		// case: cmd is in quotes
		else if (is_quote && flag_cmd == 0)
		{
			flag_cmd = 1;
			quot_mark = *str;
			str++;
			// ensures quotes are non-empty
			if (*str == quot_mark)
				return (ft_printf("Syntax error. No command provided."), 1);
		}
		// case: redirection
		else if (*str == 60 || *str == 62)
		{
			if (!(is_valid_redir(*str)))		//check: I want the pointer back after filename/delimiter
				return (ft_printf("Syntax error. Invalid redir. \n"), 1);
		}
		// case: pipe (finally!)
		else if (*str == 124)
		{
			if (flag_cmd == 0)
				return (ft_printf("Syntax error. No cmd before pipe. \n"), 1);
			str++;
			flag_cmd = 0;
		}
	}
	return (0);
}


void	parse(char *input_str, t_shell *minishell, char **env)
{


}
