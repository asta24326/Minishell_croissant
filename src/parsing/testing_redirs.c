/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:23:04 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/10 17:40:13 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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


// attention: this is double >> needs to go out here (or maybe use only once)
// works
// returns copy of the input str all bytes within quotes set to 0
// attention: I do not handle non-closed quotes (as discussed)
char	*blackout_quoted_content(char *str)
{
	char	*copy;
	char	quot_mark;
	int		i;

	copy = ft_strjoin("", str);		//memory freed in get_pipe_count
	quot_mark = 0;
	i = 0;
	while (copy[i])
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
		i++;
	}
	return (copy);
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

void	handle_redir(char *str, t_cmd *cmd)
{
	if (str[0] == '>' && str[1] != '>')
		printf("outfile!\n");
	else if (str[0] == '>' && str[1] == '>')
		printf("append\n");
	else if (str[0] == '<' && str[1] != '<')
		printf("infile\n");
	else if (str[0] == '<' && str[1] == '<')
		printf("heredoc\n");
}

int	get_redir_len(char *str)
{
	int		len;
	char	*copy;

	len = 1; //skip the (first) redir sign
	copy = blackout_quoted_content(str);
	if (copy[len] == copy[len - 1]) //case: double arrow
		len++;
	while (is_whitespace(copy[len])) //case:whitespaces in between
		len++;
	while (!is_operator(copy[len]) && !is_whitespace(copy[len]))
		while (is_quote(copy[len]) || is_other(copy[len]))
			len++;
	free (copy);
	return (len);
}

int	main(void)
{
	printf("%i\n", get_redir_len(">>file3'and 7' "));
	handle_redir("<<file3'and 7' ", NULL);
}
