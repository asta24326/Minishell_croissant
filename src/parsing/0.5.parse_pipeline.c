/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.5.parse_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:06:57 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/01 17:41:14 by kschmitt         ###   ########.fr       */
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

// goes out
int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
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

/* main data storage */
// typedef struct	s_shell
// {
// 	int		pipe_count;
// 	int		**pipes;
// 	char	**env;
// 	t_cmd	*cmd;
// 	int		exit_status;
// }	t_shell;

// works
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

// handled in exec
// creates the int array for holding fd for each pipe
// int	create_fd_storage(t_shell *minishell)
// {
// 	int	i;
// 	int	fd[2];

// 	i = -1;
// 	minishell->pipes = malloc((minishell->pipe_count + 1) * sizeof(int *));
// 	if (!minishell->pipes)
// 		return (printf("memory allocation failed in t_shell (pipes).\n"), FAILURE);
// 	while (++i < minishell->pipe_count)
// 		minishell->pipes[i] = &fd[2];
// 	minishell->pipes[i] = NULL;
// 	return (SUCCESS);
// }

// works
// extracts data for the t_shell structure
int	parse_pipeline(char *pipeline, char **env)
{
	t_shell	minishell;

	minishell.pipe_count = get_pipe_count(pipeline);
	minishell.pipes = NULL;							//handled in exec
	minishell.env = env;
	minishell.cmd = (t_cmd *)malloc(sizeof (t_cmd));
	if (!minishell.cmd)
		return (printf("memory allocation failed in t_shell (cmd).\n"), FAILURE);
	ft_memset(minishell.cmd, 0, sizeof(*minishell.cmd));	//sets node to zero
	minishell.exit_status = 0;
	return (SUCCESS);
}

// ----------for testing only-----------------------
int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	parse_pipeline("hello | string | another ||", env);
}
