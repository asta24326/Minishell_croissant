/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_quotes_cleanup.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:01:21 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/12 18:16:53 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	*found;

	found = (char *)s;
	while (*found && ((unsigned char)*found != (unsigned char)c))
		found++;
	if ((unsigned char)*found == (unsigned char)c)
	{
		return (found);
	}
	return (NULL);
}

int	is_redir(char c)
{
	if (c == 60 || c == 62)
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	is_whitespace(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == 124 || c == 60 || c == 62)
		return (1);
	return (0);
}

int	is_other(char c)
{
	if (is_whitespace(c) || is_operator(c) || is_quote(c))
		return (0);
	return (1);
}

int	get_strlen_clean(char *orig_str)
{
	int		len;
	char	quot_mark;

	len = 0;
	quot_mark = 0;
	while (*orig_str)
	{
		if (is_quote(*orig_str) && quot_mark == 0) //case: first quot mark encountered
			quot_mark = *orig_str;
		else if (*orig_str == quot_mark)
			quot_mark = 0;
		else
			len++;
		orig_str++;
	}
	return (len);
}

char	*get_clean_str(char *orig_str)
{
	char	*clean_str;
	char	quot_mark;
	int		i;
	int		j;

	clean_str = (char *)malloc(get_strlen_clean(orig_str) + 1);
	if (!clean_str)
		return (printf("Error with memory allocation.\n"), NULL);
	i = 0;
	j = 0;
	while (orig_str[i])
	{
		if (is_quote(orig_str[i]))
		{
			quot_mark = orig_str[i++];
			while (orig_str[i] != quot_mark)
				clean_str[j++] = orig_str[i++];
			i++;
		}
		else if (is_other(orig_str[i]) || is_redir(orig_str[i]))
			while (orig_str[i] && !is_quote(orig_str[i]))
				clean_str[j++] = orig_str[i++];
	}
	clean_str[j] = '\0';
	return (clean_str);
}

// works
// char	*cleanup_quotes(char *orig_str)
// {
// 	char	*clean_str;
// 	char	quot_mark;

// 	if (!ft_strchr(orig_str, '\'') && !ft_strchr(orig_str, '\"')) //case: no quotes
// 		return (orig_str);
// 	clean_str = get_clean_str(orig_str);
// 	// free(orig_str);
// 	// orig_str = NULL;
// 	return (clean_str);
// }



int	main(void)
{
	char	*arr[] = {"'<<'hi'whoop'hey!", "hello hello, no quotes in here", "'quote'on'quote\"on\"'quote'END", NULL};
	int		i;

	cleanup_quotes(arr);
	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
}
