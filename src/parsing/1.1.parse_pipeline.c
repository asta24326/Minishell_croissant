/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.1.parse_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:06:57 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/04 18:34:16 by kschmitt         ###   ########.fr       */
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

// // attention: this is double >> needs to go out here (or maybe use only once)
// // works
// // returns copy of the input str all bytes within quotes set to 0
// // attention: I do not handle non-closed quotes (as discussed)
// char	*blackout_quoted_content(char *str)
// {
// 	char	*copy;
// 	char	quot_mark;
// 	int		i;

// 	copy = ft_strjoin("", str);
// 	quot_mark = 0;
// 	i = -1;
// 	while (copy[++i])
// 	{
// 		if (is_quote(copy[i]))
// 		{
// 			quot_mark = copy[i];
// 			i++;
// 			while (copy[i] && copy[i] != quot_mark)
// 			{
// 				copy[i] = 48;
// 				i++;
// 			}
// 		}
// 	}
// 	return (copy);
// }

// works, no memory leaks
// extracts amount of pipes
int	get_pipe_count(char *pipeline)
{
	int		count;
	int		i;
	char	*copy;

	count = 0;
	i = -1;
	copy = blackout_quoted_content(pipeline);
	while (copy[++i])
		if (copy[i] == 124)
			count++;
	free(copy);
	return (count);
}

// works
// extracts data for the t_shell structure
void	parse_pipeline(char *pipeline, char **env)
{
	t_shell	minishell;

	if (!is_valid_syntax(pipeline))
		return (printf("Syntax error.\n"), FAILURE);
	minishell.pipe_count = get_pipe_count(pipeline);
	minishell.pipes = NULL; //handled in exec
	minishell.env = env;
	create_cmd_list(pipeline, minishell.pipe_count + 1, &minishell);
	minishell.exit_status = 0;
	execute(&minishell); //passing to execution
}

// ----------for testing only-----------------------
// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	parse_pipeline("hello | string | another ||", env);
// }
