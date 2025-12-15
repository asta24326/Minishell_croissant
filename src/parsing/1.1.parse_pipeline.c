/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.1.parse_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:06:57 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/12 12:56:27 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// // goes out
// size_t	ft_strlcat(char *dst, const char *src, size_t size)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = strlen(dst);
// 	if (size <= i)
// 		return (size + strlen(src));
// 	j = 0;
// 	while (src[j] && ((i + j) < (size - 1)))
// 	{
// 		dst[i + j] = src[j];
// 		j++;
// 	}
// 	dst[i + j] = '\0';
// 	return (i + strlen(src));
// }

// // goes out
// char	*ft_strjoin(const char *s1, const char *s2)
// {
// 	char	*new;
// 	size_t	len1;
// 	size_t	len2;

// 	len1 = strlen(s1);
// 	len2 = strlen(s2);
// 	new = (char *)calloc((len1 + len2 + 1), sizeof(char));
// 	if (!new)
// 		return (NULL);
// 	ft_strlcat(new, s1, len1 + 1);
// 	ft_strlcat(new, s2, len2 + len1 + 1);
// 	return (new);
// }

// // goes out
// int	is_quote(char c)
// {
// 	if (c == 34 || c == 39)
// 		return (1);
// 	return (0);
// }


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

// works, no memory leaks
// extracts data for the t_shell structure
int	parse_pipeline(char *pipeline, t_shell *minishell)
{
	char	*copy;

	copy = blackout_quoted_content(pipeline);
	if (!is_valid_syntax(copy))
		return (free(copy), FAILURE);
	minishell->pipe_count = get_pipe_count(copy);
	free(copy);
	minishell->pipes = NULL;//handled in exec
	create_cmd_list(pipeline, minishell->pipe_count + 1, minishell);
	minishell->exit_status = 0;
	execute(minishell);//passing to execution
	return (SUCCESS);
}

// ----------for testing only-----------------------
// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	parse_pipeline("hello | string | another ||", env);
// }
