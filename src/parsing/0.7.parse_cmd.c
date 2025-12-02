/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.7.parse_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:18:09 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/02 18:16:04 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ---------libft > needs to go out-----------------
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
// -----------end of libft functions------------------

// works
// checks whether cmd is built-in command
// checks exact spelling >> syntax error if not exact
// attention: I need to set flag to TRUE
int	is_builtin_cmd(char *str)
{
	if (!(ft_strcmp(str, "echo")) || !(ft_strcmp(str, "cd"))
		|| !(ft_strcmp(str, "pwd")) || !(ft_strcmp(str, "export"))
		|| !(ft_strcmp(str, "unset")) || !(ft_strcmp(str, "env"))
		|| !(ft_strcmp(str, "exit")))
		return (1);
	return (0);
}

// BIG QUESTION HERE: how do I know which argument to check (aka which one is the cmd)?
// - check for options >> syntax error if there
// - check for arguments with cmd not taking arguments >> ignore (aka do not pass)




// extracts the cmd string from the input str
// attention: needs to be set in struct
char	*parse_cmd(char *input_str)
{
	char	quot_mark;
	char	*cmd;
	int		flag_redir;
	int		i;
	int		j;

	quot_mark = 0;
	flag_redir = 0;
	i = 0;
	j = 0;
	while (input_str[i])
	{
		if (input_str[i] == 60 || input_str[i] == 62)
			flag_redir = 1;
		if (is_quote(input_str[i]) && flag_redir == 0)
		{
			quot_mark = input_str[i];
			while (input_str[i] != quot_mark && input_str[i])
			{
				cmd[j] = input_str[i];
				j++;
				i++;
				// cmd = ft_strdup(input_str + i)				//attention: memory allocation : attention: needs to be cut
			}
			cmd[j] = '\0';
		}
		if (!is_whitespace(input_str[i]) && !is_token(input_str[i]) && !is_quote(input_str[i]))
		{
			if
		}
		i++;
	}
	return (cmd);
}

// works
// needed: str with blackout quotes
// returns the number of redirs in cmd_str
int	get_redir_count(char *cmd_str)
{
	int	count;

	count = 0;
	while (*cmd_str)
	{
		// works because I excluded the pipes at this stage
		if (is_token(*cmd_str))
		{
			count++;
			// checks whether it is append or heredoc
			// works because I did syntax check before
			if (is_token(*cmd_str))
				cmd_str++;
		}
		cmd_str++;
	}
	return (count);
}

// works
// needed: str with blackout quotes
// needed: how many redirs? (also with blackout quotes)
int	get_arg_count(char *cmd_str)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (cmd_str[++i])
	{
		if (!is_whitespace(cmd_str[i]) && !is_token(cmd_str[i]))
		{
			count++;
			// whitespace and token work as delimiter
			while (cmd_str[i] && !is_whitespace(cmd_str[i])
				&& !is_token(cmd_str[i]))
				i++;
		}
	}
	// if redirs in cmd_str, substract the filename/delimiter
	return (count - (get_redir_count(cmd_str)));
}

// I AM HERE
// attention, this cannot be blackout str
char	**fillarr(char *cmd_str, char **arr)
{
	int	i;

	i = 0;
	while (*cmd_str)
	{
		while (is_whitespace(*cmd_str) || is_token(*cmd_str))
		{

		}
	}
}

// the redirs need to be identified and taken out of the equation
char	**create_cmd_arr(char *cmd_str)
{
	char	*arr;

	arr = malloc(get_arg_count(cmd_str) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (fillarr(cmd_str, arr));
}


// for testing only
int	main(void)
{
	char	**arr;
	int		i;

	arr = parse_cmd("hellloooo 'hey' oooops' where?'");
	i = -1;
	while (++i < 4)
		printf("arr[%i]: %s\n", i, arr[i]);
	return (0);
}

// int	main(void)
// {
// 	char	*str;

// 	str = "exit";
// 	if (!is_builtin_cmd(str))
// 		printf("not build-in\n");
// 	else
// 		printf("build-in\n");
// }
