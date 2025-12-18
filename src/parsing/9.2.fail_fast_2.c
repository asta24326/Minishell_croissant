/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9.2.fail_fast_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:13:02 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 13:25:44 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// #include <readline/readline.h>
// #include <readline/history.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// size_t	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (*s++)
// 		i++;
// 	return (i);
// }

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!s1)
// 		return (1);
// 	while (s1[i] || s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return (s1[i] - s2[i]);
// 		i++;
// 	}
// 	return (0);
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

// void	clean(char **result, int word_index)
// {
// 	while (word_index > 0)
// 	{
// 		word_index--;
// 		free(result[word_index]);
// 	}
// 	free(result);
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
// // ---------------  libft functions - end!  --------------

// // in
// int	is_whitespace(char c)
// {
// 	if (c == 32 || c == 9)
// 		return (true);
// 	return (false);
// }

// // in
// int	is_operator(char c)
// {
// 	if (c == '|' || c == '>' || c == '<')
// 		return (true);
// 	return (false);
// }

// // in
// int	is_redir(char c)
// {
// 	if (c == '>' || c == '<')
// 		return (true);
// 	return (false);
// }

// // in
// int	is_quote(char c)
// {
// 	if (c == '\'' || c == '\"')
// 		return (true);
// 	return (false);
// }

// // in
// int	is_other(char c)
// {
// 	if (is_whitespace(c) || is_operator(c) || is_quote(c))
// 		return (false);
// 	return (true);
// }

// // in
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
// 			while (copy[i + 1] && copy[i] != quot_mark)
// 			{
// 				copy[i] = 48;
// 				i++;
// 			}
// 		}
// 	}
// 	return (copy);
// }

// // works
// // returns length of redirection token
// int	get_redir_len(char *str)
// {
// 	int		len;
// 	char	*copy;

// 	len = 1; //skip the (first) redir sign
// 	copy = blackout_quoted_content(str);
// 	if (!copy)
// 		return (perror("blackout_quoted_content"), -1);
// 	if (copy[len] == copy[len - 1]) //case: double arrow
// 		len++;
// 	while (is_whitespace(copy[len])) //case:whitespaces in between
// 		len++;
// 	while (copy[len] && (is_quote(copy[len]) || is_other(copy[len])))
// 		len++;
// 	free (copy);
// 	return (len);
// }

// // works
// // includes the redirs/heredoc into the redirs->list
// void	fill_redirs_arr(char *redirect, t_cmd *cmd)
// {
// 	static int	i; // needed because of repeated call

// 	cmd->redirs->list[i] = redirect;
// 	i++;
// 	if (i == cmd->redirs_count) // NULL-terminate array and reset i to 0 when all cmds were handled
// 	{
// 		cmd->redirs->list[i] = NULL;
// 		i = 0;
// 	}
// }

// char	*get_delimiter(char *cmd_str, int len)
// {
// 	int	skip;

// 	skip = 0;
// 	while (is_redir(cmd_str[skip]) || is_whitespace(cmd_str[skip]))
// 		skip += 1;
// 	return (ft_substr(cmd_str, skip, len - skip));
// }

// int	prepare_hdoc(char *cmd_str, t_redirs *redirs, int len)
// {
// 	static int	nbr_hdoc;

// 	nbr_hdoc += 1;
// 	if (nbr_hdoc == redirs->hdoc_count)
// 	{
// 		redirs->hdoc_delim = get_delimiter(cmd_str, len);
// 		if (!redirs->hdoc_delim)
// 			return (perror("get_delimiter"), FAILURE);
// 		nbr_hdoc = 0;
// 	}
// 	return (SUCCESS);
// }

// // works
// // here, we look into single redirs
// // returns index after the redir token
// int	parse_redir(char *cmd_str, t_cmd *cmd)
// {
// 	int		index;
// 	char	*redirect;

// 	index = get_redir_len(cmd_str);
// 	if (index > 0)
// 	{
// 		if (cmd_str[0] == '<' && cmd_str[1] == '<') //case: heredoc
// 			if (prepare_hdoc(cmd_str, cmd->redirs, index))
// 				return (perror("parse_redir, hdoc"), -1);
// 		else //case: redir
// 		{
// 			redirect = ft_substr(cmd_str, 0, index);
// 			if (!redirect)
// 				return (perror("parse_redir, redir"),
// 					ft_free_arr(cmd->redirs->list), -1);
// 			fill_redirs_arr(redirect, cmd);
// 		}
// 	}
// 	return (index);
// }

// // works
// // returns length of cmd/flag/arg/env_arg
// int	get_arg_len(char *str)
// {
// 	int		len;
// 	char	quot_mark;

// 	len = 0;
// 	while (str[len])
// 	{
// 		if (is_quote(str[len]))
// 		{
// 			quot_mark = str[len];
// 			len += 1;
// 			while (str[len] && str[len] != quot_mark)
// 				len += 1;
// 			len += 1;
// 		}
// 		else if (is_other(str[len]))
// 			while (str[len] && !is_whitespace(str[len])
// 				&& !is_operator(str[len]) && !is_quote(str[len]))
// 				len += 1;
// 	}
// 	return (len);
// }

// // works
// // includes the cmd/flag/arg/env_arg into the args_array
// // attention, this will be called repeatedly as soon as arg is encountered
// void	fill_args_arr(char *arg, t_cmd *cmd)
// {
// 	static int	i; // needed because of repeated call

// 	cmd->args[i] = arg;
// 	i++;
// 	if (i == cmd->args_count) // NULL-terminate array and reset i to 0 when all cmds were handled
// 	{
// 		cmd->args[i] = NULL;
// 		i = 0;
// 	}
// }

// // works
// // loops through cmd/flag/arg/env_arg and returns index after last byte
// int	parse_cmd(char *cmd_str, t_cmd *cmd)
// {
// 	int		index;
// 	char	*arg;

// 	index = get_arg_len(cmd_str);
// 	arg = ft_substr(cmd_str, 0, index);
// 	if (!arg)
// 		return (perror("parse_cmd"), -1); //free array
// 	fill_args_arr(arg, cmd);
// 	// printf("[parse cmd] %s\n", cmd->args[0]);
// 	return (index);
// }

// works
// forks tokens into arguments and redirs
int	tokenize(char *cmd_str, t_cmd *cmd)
{
	int	index;

	index = 0;
	while (*cmd_str) // loops through cmd_str and sets i to byte after operator
	{
		if (is_quote(*cmd_str) || is_other(*cmd_str))
			index = parse_cmd(cmd_str, cmd);
		else if (is_redir(*cmd_str))
			index = parse_redir(cmd_str, cmd);
		else
			index = 1;
		if (index == -1)
			return (FAILURE);
		cmd_str += index;
	}
	return (SUCCESS);
}

// // works
// int	get_hdoc_count(char *cmd_str)
// {
// 	int		i;
// 	int		count;
// 	char	*copy;

// 	i = -1;
// 	count = 0;
// 	copy = blackout_quoted_content(cmd_str);
// 	if (!copy)
// 		return (perror("blackout_quoted_content"), FAILURE);
// 	while (cmd_str[++i])
// 		if (cmd_str[i] == '<' && cmd_str[i + 1] == '<')
// 			count += 1;
// 	free (copy);
// 	return (count);
// }

// int	prepare_redirs(char *cmd_str, t_cmd *cmd)
// {
// 	t_redirs	*redirects;

// 	redirects = (t_redirs *)malloc(sizeof(t_redirs));
// 	if (!redirects)
// 		return (perror("prepare_redirs, struct"), FAILURE);
// 	redirects->list = ft_calloc(cmd->redirs_count + 1, sizeof(char *));
// 	if (!redirects->list)
// 		return (perror("prepare_redirs, list"), FAILURE);
// 	redirects->in_fd = 0;
// 	redirects->out_fd = 0;
// 	redirects->append_fd = 0;
// 	redirects->hdoc_count = get_hdoc_count(cmd_str); //needed? check how often used in the end //RAUS bitte, sonst error handling
// 	redirects->hdoc_delim = NULL;
// 	redirects->exp_hdoc = NULL; //needed? rather NO
// 	cmd->redirs = redirects;
// 	return (SUCCESS);
// }

// //works
// // returns amout of redirs in 1 cmd_line
// int	get_redir_count(char *copy)
// {
// 	int		count;
// 	int		i;

// 	count = 0;
// 	i = -1;
// 	while (copy[++i])
// 	{
// 		if (is_redir(copy[i]))
// 		{
// 			count++;
// 			i++;
// 			if (is_redir(copy[i]))
// 				i++;
// 		}
// 	}
// 	return (count);
// }

// // works
// // returns the amout of arguments in 1 cmd_line
// int	get_arg_count(char *copy)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	i = -1;
// 	while (copy[++i])
// 	{
// 		if (!is_whitespace(copy[i]) && !is_operator(copy[i]))
// 		{
// 			count++;
// 			while (copy[i] && !is_whitespace(copy[i]) // whitespace and operator work as delimiter
// 				&& !is_operator(copy[i]))
// 				i++;
// 		}
// 	}
// 	return (count);
// }

// // works, no memory leaks
// // sets the arg_count and the args_arr for cmd node
// void	prepare_args_arr(char *cmd_str, t_cmd *cmd)
// {
// 	char	*copy;

// 	copy = blackout_quoted_content(cmd_str);
// 	if (!copy)
// 		return (perror("blackout_quoted_content"), FAILURE);
// 	cmd->redirs_count = get_redir_count(copy);
// 	cmd->args_count = get_arg_count(copy) - cmd->redirs_count;
// 	free (copy);
// 	cmd->args = calloc(cmd->args_count + 1, sizeof(char *)); //attention: memory allocation // calloc needed as single strings are not filled immediatly
// }

// // works
// // creates t_cmd node
// t_cmd	*create_node(char *cmd_line)
// {
// 	t_cmd	*new;

// 	new = (t_cmd *)malloc(sizeof(t_cmd));
// 	if (!new)
// 		return (perror("create_node"), NULL);
// 	prepare_args_arr(cmd_line, new);//creates char **args, int args_count, int redirs_count
// 	new->builtin = NULL;
// 	if (new->redirs_count > 0)
// 		prepare_redirs(cmd_line, new);
// 	else
// 		new->redirs = NULL;
// 	new->next = NULL;
// 	return (new);
// }

// // works
// // adds a new node to the back of the linked list
// void	add_node(t_cmd **list, t_cmd *new)
// {
// 	t_cmd	*head;

// 	head = *list;
// 	while (head != NULL && head->next != NULL)
// 		head = head->next;
// 	head->next = new;
// }

// void	set_index(t_cmd *stack, int cmd_count)
// {
// 	int		i;
// 	t_cmd	*current;

// 	i = -1;
// 	current = stack;
// 	while (++i < cmd_count)
// 	{
// 		current->index = i;
// 		current = current->next;
// 	}
// }

// // // goes out - only for testing
// // void	print_list(t_cmd *list, int cmd_count)
// // {
// // 	int	i;

// // 	i = 0;
// // 	while (i < cmd_count)
// // 	{
// // 		printf("i = %i\n", i);
// // 		printf("tadaaaa: %s\n", list->args[0]);
// // 		list = list->next;
// // 		i++;
// // 	}
// // }

// // to be tested
// // splits pipeline into cmd-lines, and creates 1 node per cmd-line
// // attention: what I need here to be passed is blacked out string!
// void	create_cmd_list(char **arr, int cmd_count, t_shell *minishell)
// {
// 	t_cmd	*list;
// 	int		i;

// 	list = create_node(arr[0]);//initiates the list, creates first node
// 	i = 0;
// 	while (++i < cmd_count) //creates entire list by passing 1 cmd-line per node
// 		add_node(&list, create_node(arr[i]));
// 	// print_list(list, cmd_count);
// 	set_index(list, cmd_count);
// 	minishell->cmd = list;
// }

// // works
// // returns length of str cleaned by quotes to be removed
// int	get_strlen_clean(char *orig_str)
// {
// 	int		len;
// 	char	quot_mark;

// 	len = 0;
// 	quot_mark = 0;
// 	while (*orig_str)
// 	{
// 		if (is_quote(*orig_str) && quot_mark == 0) //first quot.mark encountered
// 			quot_mark = *orig_str;
// 		else if (*orig_str == quot_mark) //matching quot.mark encountered
// 			quot_mark = 0;
// 		else
// 			len++;
// 		orig_str++;
// 	}
// 	return (len);
// }

// // works
// // returns a string witout quotes that will not be outputted
// // pre-condition: functioning operators, unecessary whitespaces and to be expanded $ have been gone
// char	*get_clean_str(char *orig_str)
// {
// 	char	*clean_str;
// 	char	quot_mark;
// 	int		i;
// 	int		j;

// 	clean_str = (char *)malloc(get_strlen_clean(orig_str) + 1);
// 	if (!clean_str)
// 		return (perror("get_clean_str"), NULL);
// 	i = 0;
// 	j = 0;
// 	while (orig_str[i])
// 	{
// 		if (is_quote(orig_str[i]))
// 		{
// 			quot_mark = orig_str[i++];
// 			while (orig_str[i] != quot_mark)
// 				clean_str[j++] = orig_str[i++];
// 			i++;
// 		}
// 		else if (is_other(orig_str[i]) || is_redir(orig_str[i]))
// 			while (orig_str[i] && !is_quote(orig_str[i]))
// 				clean_str[j++] = orig_str[i++];
// 	}
// 	clean_str[j] = '\0';
// 	return (free(orig_str), clean_str);
// }

// // works
// // cleans the passed char *arr from unnecessary quotes
// // needed for char **args and for char **redirs
// void	cleanup_quotes(char **arr)
// {
// 	int		i;

// 	i = -1;
// 	// printf("orig: %s\n", arr[0]);
// 	while (arr[++i])
// 	{
// 		if (strchr(arr[i], '\'') || strchr(arr[i], '\"'))
// 		{
// 			arr[i] = get_clean_str(arr[i]);
// 			if (!arr[i])
// 				ft_free(arr); //to include from kristin's ft_split
// 		}
// 	}
// }

// int	is_builtin_cmd(t_cmd *cmd)
// {
// 	char	*str;

// 	str = cmd->args[0];
// 	if (!(ft_strcmp(str, "echo")) || !(ft_strcmp(str, "cd"))
// 		|| !(ft_strcmp(str, "pwd")) || !(ft_strcmp(str, "export"))
// 		|| !(ft_strcmp(str, "unset")) || !(ft_strcmp(str, "env"))
// 		|| !(ft_strcmp(str, "exit")))
// 		return (true);
// 	return (false);
// }

// // works
// // attention: here, I need the index of the cmd
// int	handle_outfile(char *filename, t_cmd *cmd)
// {
// 	static int	fd;
// 	static int	cmd_index;

// 	if (cmd_index != cmd->index)//case: we arrived at next cmd
// 	{
// 		cmd_index = cmd->index;
// 		fd = 0;
// 	}
// 	if (fd > 0)//case:several outfiles in 1 cmd
// 		close (fd);
// 	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		return (perror("handle_outfile"), FAILURE);
// 	cmd->redirs->out_fd = fd;
// 	free (filename);
// 	return (SUCCESS);
// }

// //attention: here, I need the index of the cmd
// //attention: here, I need int append_fd in t_redirs
// int	handle_append(char *filename, t_cmd *cmd)
// {
// 	static int	fd;
// 	static int	cmd_index;

// 	if (cmd_index != cmd->index)//case: we arrived at next cmd
// 	{
// 		cmd_index = cmd->index;
// 		fd = 0;
// 	}
// 	if (fd > 0)//case:several appends in 1 cmd
// 		close (fd);
// 	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd == -1)
// 		return (perror("handle_append"), FAILURE);
// 	cmd->redirs->append_fd = fd;
// 	free (filename);
// 	return (SUCCESS);
// }

// //attention: here, I need the index of the cmd
// int	handle_infile(char *filename, t_cmd *cmd)
// {
// 	static int	fd;
// 	static int	cmd_index;

// 	if (cmd_index != cmd->index)//case: we arrived at next cmd
// 	{
// 		cmd_index = cmd->index;
// 		fd = 0;
// 	}
// 	if (fd > 0)//case:several infiles in 1 cmd
// 		close (fd);
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return (perror("handle_infile"), FAILURE);
// 	if (cmd->redirs->hdoc_delim != NULL) //only if heredoc exists
// 	{
// 		close (fd);
// 		fd = 0;
// 	}
// 	cmd->redirs->in_fd = fd;
// 	free (filename);
// 	return (SUCCESS);
// }

// //attention: here, I need the index of the cmd
// // pre-condition: quotes were handled (aka eliminated)
// // means: bool exp_hdoc was extracted while quote handling
// // int	handle_heredoc(char *filename, t_cmd *cmd)
// // {
// // 	if (cmd->redirs->hdoc_delim != NULL)//case: multiple heredocs
// // 	{
// // 		free(cmd->redirs->hdoc_delim);
// // 		cmd->redirs->hdoc_delim == NULL;
// // 	}
// // 	cmd->redirs->hdoc_delim = filename;
// // 	return (SUCCESS);
// // }

// // works
// // returns the filename/delimiter
// // pre-condition: quotes were handled (aka eliminated)
// char	*get_filename(char *redir_str)
// {
// 	int	skip;
// 	int	len;

// 	skip = 0;
// 	len = ft_strlen(redir_str);
// 	while (is_redir(redir_str[skip]) || is_whitespace(redir_str[skip]))
// 		skip++;
// 	return (ft_substr(redir_str, skip, len - skip));
// }

// // works
// // handles the redir depending on the type
// int	handle_redirs(t_cmd *cmd)
// {
// 	int		i;
// 	char	**redir_list;
// 	char	*filename;

// 	i = -1;
// 	redir_list = cmd->redirs->list;
// 	while (redir_list[++i])
// 	{
// 		filename = get_filename(redir_list[i]);
// 		if (!filename)
// 			return (perror("get_filename"), FAILURE);
// 		if (redir_list[i][0] == '>' && redir_list[i][1] != '>')
// 			handle_outfile(filename, cmd);
// 		else if (redir_list[i][0] == '>' && redir_list[i][1] == '>')
// 			handle_append(filename, cmd);
// 		else if (redir_list[i][0] == '<' && redir_list[i][1] != '<')
// 			handle_infile(filename, cmd);
// 		// else if (redir_list[i][0] == '<' && redir_list[i][1] == '<')
// 		// 	handle_heredoc(get_filename(redir_list[i], 2), cmd);//done by Aidar
// 	}
// 	if (cmd->redirs->out_fd > 0 && cmd->redirs->append_fd > 0) //case: out & append, only out is passed
// 	{
// 		close (cmd->redirs->append_fd);
// 		cmd->redirs->append_fd = 0;
// 	}
// 	return (free(cmd->redirs->list), SUCCESS);
// }


// works
// needed: error handling
int	parse_cmd_lines(char *pipeline, int cmd_count, t_shell *minishell)
{
	char	**arr;
	t_cmd	*head;
	int		i;

	arr = ft_split(pipeline, 124);//splits the pipeline into its cmd-lines
	if (!arr)
		return (perror("parse_cmd_line"), FAILURE);
	create_cmd_list(arr, cmd_count, minishell);
	head = minishell->cmd;
	i = -1;
	while (++i < cmd_count)
	{
		tokenize(arr[i], minishell->cmd);
		// handle_heredoc();
		// expand_env_var();
		cleanup_quotes(minishell->cmd->args);
		minishell->cmd->builtin = is_builtin_cmd(minishell->cmd);
		if (minishell->cmd->redirs_count > 0)
		{
			cleanup_quotes(minishell->cmd->redirs->list);
			handle_redirs(minishell->cmd);
		}
		minishell->cmd = minishell->cmd->next;
	}
	minishell->cmd = head;
	return (clean(arr, cmd_count), SUCCESS);
}

// // works
// // extracts amount of pipes
// int	get_pipe_count(char *copy)
// {
// 	int		count;
// 	int		i;

// 	count = 0;
// 	i = -1;
// 	while (copy[++i])
// 		if (copy[i] == 124)
// 			count++;
// 	return (count);
// }

// // works
// // extracts data for the t_shell structure
// void	prepare_parsing(char *copy, t_shell *minishell)
// {
// 	minishell->pipe_count = get_pipe_count(copy);
// 	minishell->pipes = NULL; //handled in exec
// 	minishell->cmd = NULL;
// 	minishell->exit_status = 0;
// 	minishell->shell_pid = getpid();
// }

// // works
// // checks whether pipe is valid (it needs at least 1 cmd or 1 redir on left side)
// int	are_valid_pipes(char *copy)
// {
// 	int	flag;

// 	flag = 0;
// 	while (*copy)
// 	{
// 		if (is_quote(*copy) || is_redir(*copy) || is_other(*copy))
// 			flag = 1;
// 		else if (*copy == 124)
// 		{
// 			if (flag == 0)
// 				return (false);
// 			flag = 0;
// 		}
// 		copy++;
// 	}
// 	return (true);
// }

// // works
// // checks whether redirection has exactly 1 or 2 same arrows, +filename/delimiter
// int	are_valid_redirs(char *copy)
// {
// 	int		i;

// 	i = -1;
// 	while (copy[++i])
// 	{
// 		if (is_redir(copy[i]))
// 		{
// 			i++;
// 			if (copy[i] == copy[i - 1]) //case: double arrow
// 				i++;
// 			while (is_whitespace(copy[i]))
// 				i++;
// 			while (is_quote(copy[i])) //case:quoted filename/delimiter
// 				i++;
// 			if (!is_other(copy[i]) || !copy[i]) //MUST be other
// 				return (false);
// 		}
// 	}
// 	return (true);
// }

// // works
// // checks whether quotes are closed
// int	are_closed_quotes(char *copy)
// {
// 	char	quot_mark;

// 	quot_mark = 0;
// 	while (*copy)
// 	{
// 		if (is_quote(*copy) & !quot_mark)
// 			quot_mark = *copy;
// 		else if (*copy == quot_mark)
// 			quot_mark = 0;
// 		copy++;
// 	}
// 	if (quot_mark == 0)
// 		return (true);
// 	return (false);
// }

// // works, no memory leaks
// // checks overall syntax of input pipeline
// int	is_valid_syntax(char *copy)
// {
// 	if (!are_valid_pipes(copy))
// 		return (printf("Syntax error. Pipe(s) invalid.\n"), false);
// 	if (!are_valid_redirs(copy))
// 		return (printf("Syntax error. Redir(s) invalid.\n"), false);
// 	if (!are_closed_quotes(copy))
// 		return (printf("Syntax error. Unclosed quote(s).\n"), false);
// 	return (true);
// }


// // goes out - only for testing
// void	print_list(t_cmd *cmd, int cmd_count)
// {
// 	int		i;
// 	int		j;
// 	t_cmd	*current;

// 	i = 0;
// 	current = cmd;
// 	printf("------------- ARGS -------------\n");
// 	while (i < cmd_count)
// 	{
// 		printf("i: %i\n", i);
// 		printf("index: %i\n", current->index);
// 		printf("tadaaaa (args): [%s]\n", current->args[0]);
// 		printf("is builtin: %i\n\n", current->builtin);
// 		j = 0;
// 		printf("------------- REDIRS -------------\n");
// 		while (current->redirs_count > 0)
// 		{
// 			printf("tadaaaa (redirs): %s\n", current->redirs->list[j]);
// 			j++;
// 			current->redirs_count--;
// 		}
// 		printf("in_fd: %i\n", current->redirs->in_fd);
// 		printf("out_fd: %i\n", current->redirs->out_fd);
// 		printf("append_fd: %i\n", current->redirs->append_fd);
// 		printf("hdoc_delim: [%s]\n", current->redirs->hdoc_delim);
// 		current = current->next;
// 		i++;
// 	}
// }

// int	parse(char *pipeline, t_shell *minishell)
// {
// 	char	*copy;

// 	copy = blackout_quoted_content(pipeline);
// 	if (!copy)
// 		return (perror("blackout_quoted_content"), FAILURE);
// 	if (!is_valid_syntax(copy))
// 		return (free(copy), FAILURE);
// 	prepare_parsing(copy, minishell);
// 	free(copy);
// 	parse_cmd_lines(pipeline, minishell->pipe_count + 1, minishell); //error handling
// 	// printf("[parse] %s\n", minishell->cmd->args[0]);
// 	// print_list(minishell->cmd, minishell->pipe_count + 1);
// 	return (SUCCESS);
// }

// void	end_minishell(t_shell *minishell)
// {
// 	free(minishell->prompt);
// 	free(minishell->env);
// 	free(minishell);
// 	minishell = NULL;
// 	rl_clear_history();
// }

// // in
// void	handle_signal_parent(int signum)
// {
// 	(void)signum;
// 	printf("\n");
// 	rl_on_new_line();//updates about jump to next line
// 	// rl_replace_line("", 0);//clears current buffer //not needed
// 	rl_redisplay();//refreshes readline prompt
// 	return ;
// }

// // in
// void	setup_signals(void (*signal_handler)(int))
// {
// 	signal(SIGINT, signal_handler); //case: ctrl-C
// 	signal(SIGQUIT, SIG_IGN); //case: ctrl-\ - is ignored
// }

// // works
// // sets the prompt, reads the user input and saves it into a char *buffer
// // program loop with signal handling
// // creates and continously adds to history if input is non-empty
// int	init_minishell(t_shell *minishell)
// {
// 	char	*input_str;

// 	minishell->prompt = ft_strjoin(getenv("USER"), "@minishell: ");
// 	setup_signals(handle_signal_parent);
// 	while (1)
// 	{
// 		input_str = readline(minishell->prompt);
// 		if (!input_str)// exits in case of ctrl-D
// 		{
// 			printf("exit\n");
// 			exit(1);
// 		}
// 		if (*input_str)
// 		{
// 			if (parse_pipeline(input_str, minishell))
// 			{
// 				free(input_str);
// 				exit(1);
// 			}
// 			// execute(minishell);
// 			add_history(input_str); //adds user input to history
// 			free(input_str);
// 		}
// 	}
// 	return (0);
// }

// int	main(int ac, char **av, char **env)
// {
// 	t_shell	*minishell;

// 	(void)ac;
// 	(void)av;
// 	minishell = (t_shell *)malloc(sizeof(t_shell));
// 	if (!minishell)
// 		return (perror("t_shell memory allocation"), FAILURE);
// 	minishell->env = ft_env_dup(env);
// 	if (!minishell->env)
// 		return (free(minishell), FAILURE);
// 	init_minishell(minishell);
// 	end_minishell(minishell);
// 	return (SUCCESS);
// }
