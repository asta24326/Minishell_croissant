/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_again.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:08:48 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/10 13:15:48 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// goes out
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = strlen(dst);
	if (size <= i)
		return (size + strlen(src));
	j = 0;
	while (src[j] && ((i + j) < (size - 1)))
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + strlen(src));
}

// goes out
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	len1 = strlen(s1);
	len2 = strlen(s2);
	new = (char *)calloc((len1 + len2 + 1), sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcat(new, s1, len1 + 1);
	ft_strlcat(new, s2, len2 + len1 + 1);
	return (new);
}

// works
// checks whether c is space or horizontal tab
// attention: without '\n'
int	is_whitespace(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

// works
// checks whether c is pipe, right or left arrow
int	is_operator(char c)
{
	if (c == 124 || c == 60 || c == 62)
		return (1);
	return (0);
}

// works
// checks whether c is right or left arrow
int	is_redir(char c)
{
	if (c == 60 || c == 62)
		return (1);
	return (0);
}

// works
// checks whether c is double or single quotation mark
int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

// works
// checks whether c is cmd/arg/flag/filename/delimiter
int	is_other(char c)
{
	if (is_whitespace(c) || is_operator(c) || is_quote(c))
		return (0);
	return (1);
}


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

// works
// returns copy of the input str all bytes within quotes set to 0
// attention: I do not handle non-closed quotes (as discussed)
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
			while (copy[i] && copy[i] != quot_mark)
			{
				copy[i] = 48;
				i++;
			}
		}
	}
	return (copy);
}

// works
// extracts amount of pipes
int	get_pipe_count(char *copy)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (copy[++i])
		if (copy[i] == 124)
			count++;
	return (count);
}

// works, memory leaks
// extracts data for the t_shell structure
int	parse_pipeline(char *pipeline, char **env)
{
	char	*copy;
	t_shell	*minishell;

	copy = blackout_quoted_content(pipeline);
	if (!is_valid_syntax(copy))
		return (free(copy), FAILURE);
	minishell = (t_shell *)malloc(sizeof(t_shell));
	if (!minishell)
		return (printf("Memory allocation failed.\n"), free(copy), FAILURE);
	minishell->pipe_count = get_pipe_count(copy);
	free(copy);
	minishell->pipes = NULL; //handled in exec
	minishell->env = env;
	// create_cmd_list(pipeline, minishell->pipe_count + 1, minishell);
	minishell->exit_status = 0;
	// execute(minishell); //passing to execution
	return (SUCCESS);
}

int	main(void)
{
	printf("%i\n", parse_pipeline("helloooo | and this another cmd str!! | >>''redir'1''' | >>  file1 <file3 <<'file2'", NULL));
}
