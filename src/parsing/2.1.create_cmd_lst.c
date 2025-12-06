/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.1.create_cmd_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:40:26 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/04 18:19:35 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ---------------  libft functions - need to go out!  --------------
// char	*ft_strdup(const char *s)
// {
// 	int		i;
// 	char	*d;

// 	i = 0;
// 	d = malloc(strlen(s) + 1);
// 	if (!d)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		d[i] = s[i];
// 		i++;
// 	}
// 	d[i] = '\0';
// 	return (d);
// }

// size_t	ft_strlcpy(char *dest, const char *src, size_t size)
// {
// 	const char	*ptr;

// 	ptr = src;
// 	if (size == 0)
// 		return (strlen(src));
// 	if (size != 0)
// 	{
// 		while (size > 1 && *src)
// 		{
// 			*dest++ = *src++;
// 			size--;
// 		}
// 		*dest = '\0';
// 	}
// 	return (strlen(ptr));
// }

// char	*ft_strrchr(const char *s, int c)
// {
// 	int	i;

// 	i = strlen(s);
// 	while (i >= 0)
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)(s + i));
// 		i--;
// 	}
// 	return (NULL);
// }

// char	*ft_substr(const char *s, unsigned int start, size_t len)
// {
// 	char			*sub;
// 	unsigned int	max;

// 	if (!s)
// 		return (NULL);
// 	max = strlen(s);
// 	if ((start >= max) || len == 0)
// 		return (ft_strdup(""));
// 	if (len > (size_t)strlen(s + start))
// 		len = (size_t)strlen(s + start);
// 	sub = malloc((len + 1) * sizeof(char));
// 	if (!sub)
// 		return (NULL);
// 	s += start;
// 	if (start < max)
// 		ft_strlcpy(sub, s, len + 1);
// 	return (sub);
// }

// static int	ft_strcount(const char *s, char c)
// {
// 	int	count;

// 	count = 0;
// 	while (*s)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		if (*s && *s != c)
// 			count++;
// 		while (*s && *s != c)
// 			s++;
// 	}
// 	return (count);
// }

// static int	ft_strlength(const char *s, char c)
// {
// 	int		length;

// 	if (!ft_strrchr(s, c))
// 		length = strlen(s);
// 	else
// 	{
// 		length = 0;
// 		while (*s && *s == c)
// 			s++;
// 		while (*s && *s != c)
// 		{
// 			length++;
// 			s++;
// 		}
// 	}
// 	return (length);
// }

// static void	ft_free(char **arr_split)
// {
// 	int	i;

// 	i = 0;
// 	while (arr_split[i])
// 	{
// 		free(arr_split[i]);
// 		i++;
// 	}
// 	free(arr_split);
// }

// static char	**ft_fillarr(char const *s, char c, char **arr_split)
// {
// 	int		i;

// 	i = 0;
// 	while (*s)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		if (*s && *s != c)
// 		{
// 			arr_split[i] = ft_substr(s, 0, ft_strlength(s, c));
// 			if (!arr_split[i])
// 			{
// 				ft_free(arr_split);
// 				return (NULL);
// 			}
// 			s += ft_strlength(s, c);
// 			i++;
// 		}
// 	}
// 	arr_split[i] = NULL;
// 	return (arr_split);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**arr_split;

// 	if (s)
// 		arr_split = calloc((ft_strcount(s, c) + 1), sizeof(char *));
// 	if (!s || !arr_split)
// 		return (NULL);
// 	return (ft_fillarr(s, c, arr_split));
// }

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

// char	*blackout_quoted_content(char *str)
// {
// 	char	*copy;
// 	char	quot_mark;
// 	int		i;

// 	copy = ft_strjoin("", str);		//memory freed in get_pipe_count
// 	quot_mark = 0;
// 	i = 0;
// 	while (copy[i])
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
// 		i++;
// 	}
// 	return (copy);
// }

// // needs to go out
// int	is_quote(char c)
// {
// 	if (c == 34 || c == 39)
// 		return (1);
// 	return (0);
// }
// ----------until here, everything goes out--------------


// works
// creates t_cmd node
t_cmd	*create_node(char *cmd_line)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (printf("Error with node creation.\n"), NULL);
	//extracts char **args and int arg_count;
	create_args_arr(cmd_line, new);
	new->builtin = is_builtin_cmd(cmd_line); //only when I identified cmd - TODO
	new->redirs = extract_redir_data(cmd_line); //will be handled in parse_redir - TODO
	new->next = NULL;
	return (new);
}

// works
// adds a new node to the back of the linked list
void	add_node(t_cmd **list, t_cmd *new)
{
	t_cmd	*head;

	head = *list;
	while (head != NULL && head->next != NULL)
		head = head->next;
	head->next = new;
}

// // goes out - only for testing
// void	print_list(t_cmd *list)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 5)
// 	{
// 		printf("i = %i\n", i);
// 		printf("tadaaaa: %s\n", list->args[0]);
// 		list = list->next;
// 		i++;
// 	}
// }

// to be tested
// splits pipeline into cmd-lines, and creates 1 node per cmd-line
// attention: what I need here to be passed is blacked out string!
void	create_cmd_list(char *pipeline, int cmd_count, t_shell *minishell)
{
	char	**arr;
	t_cmd	*list;
	int		i;

	// splits the pipeline into its cmd-lines
	arr = ft_split(pipeline, 124); //memory allocation
	// initiates the list, creates first node with entire cmd line
	list = create_node(arr[0]);
	i = 0;
	// creates entire list by passing 1 cmd-line per node
	while (++i < cmd_count)
		add_node(&list, create_node(arr[i]));
	// print_list(list);
	minishell->cmd = list;
	//free arr here?
}

// ----------for testing only-----------------------
// int	main(void)
// {
// 	t_shell	minishell;
// 	t_cmd	*the_list;
// 	int		pipecount;

// 	pipecount = 0;
// 	minishell.pipe_count = 4;
// 	the_list = create_cmd_list("hello | string | another sk8ter | whoop whoop | END", minishell);
// 	while (pipecount < 4)
// 	{
// 		printf("%s\n", the_list->args);
// 		pipecount++;
// 		the_list = the_list->next;
// 	}
// }
