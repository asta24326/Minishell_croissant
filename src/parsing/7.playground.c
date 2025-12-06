/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7.playground.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:24:38 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/04 18:15:37 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

// works
// checks whether c is pipe, right or left arrow
int	is_token(char c)
{
	if (c == 124 || c == 60 || c == 62)
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
// checks whether c is '$' (prefix for env. arg.) or '-' (prefix for flag)
int	is_prefix(char c)
{
	if (c == 36 || c == 45)
		return (1);
	return (0);
}

// checks whether c is cmd/arg/flag/filename/delimiter
int	is_other(char c)
{
	if (is_whitespace(c) || is_token(c) || is_quote(c))
		return (0);
	return (1);
}

//----------------------------------------------------------

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


// ------------needs to go out---------------------
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*dest;
	size_t	i;

	i = 0;
	s_len = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (s_len + 1));
	if (dest == NULL)
		return (NULL);
	while (s_len > i)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	str_len;
	size_t	i;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (len > i)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
// ------------END (needs to go out)---------------------

// returns length of cmd/flag/arg/env_arg
int	get_arg_len(char *str)
{
	int	len;

	len = 0;
	while (!is_whitespace(*str) && !is_token(*str))
	{
		len++;
		str++;
	}
	return (len);
}

// loops through cmd/flag/arg/env_arg and returns index after quote
// int	parse_cmd(char *str, t_shell *minishell)
int	parse_cmd(char *str)
{
	int		index;
	char	*arg;

	index = get_arg_len(str);
	printf("%i\n", index);
	arg = ft_substr(str, 0, index); // attention: memory allocation
	printf("%s\n", arg);
// >> add it to char **args
	return (index);
}


// void	tokenize(char *cmd_str, t_shell *minishell)
void	tokenize(char *cmd_str)
{
	int	i;

	i = 0;
	// loops through cmd_str and sets i to byte after token
	printf("start:%s\n", cmd_str);
	while (cmd_str[i])
	{
		if (is_quote(cmd_str[i]))
		{
			// cmd_str += parse_quote(cmd_str + i);
			cmd_str += 8;
			printf("quote!-%s\n", cmd_str);
		}
		if (is_other(cmd_str[i]))
		{
			// cmd_str += parse_cmd(cmd_str + i);
			cmd_str += 7;
			printf("other!-%s\n", cmd_str);
		}
		// works because at this point, the pipe tokens were taken out already
		if (is_token(cmd_str[i]))
		{
			// cmd_str += parse_redir(cmd_str + i);
			cmd_str += 6;
			printf("token!-%s\n", cmd_str);
		}
		cmd_str++;
	}
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

//works
// returns amout of redirs in 1 cmd_line
int	get_redir_count(char *copy)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (copy[++i])
	{
		// works because pipes have been taken out and quotes are blacked out
		if (is_token(copy[i]))
		{
			count++;
			i++;
			if (is_token(copy[i]))
				i++;
		}
	}
	return (count);
}

// works
// returns the amout of arguments in 1 cmd_line
int	get_arg_count(char *copy)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (copy[++i])
	{
		if (!is_whitespace(copy[i]) && !is_token(copy[i]))
		{
			count++;
			// whitespace and token work as delimiter
			while (copy[i] && !is_whitespace(copy[i])
				&& !is_token(copy[i]))
				i++;
		}
	}
	// if redirs in cmd_str, substract the filename/delimiter
	return (count - get_redir_count(copy));
}

// to be tested
// attention, this will be called repeatedly as soon as arg is encountered
void	fill_args_arr(char *arg_str, t_cmd *cmd)
{
	static int	i; // needed because of repeated call

	cmd->args[i] = arg_str;
	i++;
	// NULL-terminate array and reset i to 0 when all cmds were handled
	if (i == cmd->arg_count)
	{
		cmd->args[i] = NULL;
		i = 0;
	}
}

// to be tested
// this can go into parse_pipeline
// the redirs need to be identified and taken out of the equation
void	create_args_arr(char *cmd_str, t_cmd *cmd)
{
	char	*copy;

	copy = blackout_quoted_content(cmd_str);
	cmd->arg_count = get_arg_count(copy);
	// calloc needed as single strings are not filled immediatly
	cmd->args = calloc(cmd->arg_count + 1, sizeof(char *)); //attention: memory allocation
	free (copy);
}

// int	main(void)
// {
// 	t_cmd	cmd;
// 	int		i;

// 	i = 0;
// 	create_args_arr("hello3. <($ARG  'whooop' hey", &cmd);
// 	printf("args count = %i\n", cmd.arg_count);
// 	fill_args_arr("args", &cmd);
// 	fill_args_arr("'whooop'", &cmd);
// 	fill_args_arr("hey", &cmd);
// 	while (i < cmd.arg_count)
// 	{
// 		printf("arg[%i]: %s\n", i, cmd.args[i]);
// 		i++;
// 	}
// }

// t_cmd	*create_cmd_list(char *pipeline, int cmd_count, t_shell *minishell)
// {
// 	char	**arr;
// 	t_cmd	*list;
// 	int		i;

// 	// splits the pipeline into its cmd-lines
// 	arr = ft_split(pipeline, 124);
// 	// initiates the list, creates first node with entire cmd line
// 	list = create_node(arr[0]);
// 	printf("first node: %s\n", list->args);
// 	i = 0;
// 	// creates entire list by passing 1 cmd-line per node
// 	while (++i < cmd_count)
// 		add_node(&list, create_node(arr[i]));
// 	// print_list(list);
// 	minishell->cmd = list;
// 	ft_free_arr(arr); // double check if ready for freeing here already, include function into libft if not there
// 	return (list);
// }

// // works
// // extracts data for the t_shell structure
// void	parse_pipeline(char *pipeline, char **env)
// {
// 	t_shell	minishell;

// 	// if (!is_valid_syntax(pipeline))
// 	// 	return (printf("Syntax error.\n"), FAILURE);
// 	// minishell.pipe_count = get_pipe_count(pipeline);
// 	// minishell.pipes = NULL; //handled in exec
// 	minishell.env = env;
// 	create_cmd_list(pipeline, minishell.pipe_count + 1, &minishell);
// 	minishell.exit_status = 0;
// 	// execute(&minishell); //passing to execution
// }

// ----------for testing only-----------------------
// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	parse_pipeline("hello | string | another ||", env);
// }

static int	ft_strcount(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

static int	ft_strlength(const char *s, char c)
{
	int		length;

	if (!ft_strrchr(s, c))
		length = strlen(s);
	else
	{
		length = 0;
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			length++;
			s++;
		}
	}
	return (length);
}

static void	ft_free(char **arr_split)
{
	int	i;

	i = 0;
	while (arr_split[i])
	{
		free(arr_split[i]);
		i++;
	}
	free(arr_split);
}

static char	**ft_fillarr(char const *s, char c, char **arr_split)
{
	int		i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			arr_split[i] = ft_substr(s, 0, ft_strlength(s, c));
			if (!arr_split[i])
			{
				ft_free(arr_split);
				return (NULL);
			}
			s += ft_strlength(s, c);
			i++;
		}
	}
	arr_split[i] = NULL;
	return (arr_split);
}

char	**ft_split(char const *s, char c)
{
	char	**arr_split;

	if (s)
		arr_split = calloc((ft_strcount(s, c) + 1), sizeof(char *));
	if (!s || !arr_split)
		return (NULL);
	return (ft_fillarr(s, c, arr_split));
}

// WIP
// creates t_cmd node
t_cmd	*create_node(char *cmd_line)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (printf("Error with node creation.\n"), NULL);
	//extracts char **args and int arg_count;
	create_args_arr(cmd_line, new);
	new->args[0] = cmd_line;
	// printf("created: %s\n", new->args[0]);
	// new->builtin = is_builtin_cmd(cmd_line); //only when I identified cmd - TODO
	// new->redirs = extract_redir_data(cmd_line); //will be handled in parse_redir - TODO
	new->next = NULL;
	return (new);
}

// t_cmd	*find_last(t_cmd *lst)
// {
// 	while (lst != NULL && lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }

// void	add_node(t_cmd **lst, t_cmd *new)
// {
// 	t_cmd	*last;

// 	// printf("[0]%s\n", *(lst)->args[0]);
// 	// printf("new: %s\n", new->args[0]);
// 	// if (!*lst)
// 	// 	*lst = new;
// 	// else
// 	// {
// 		last = find_last(*lst);
// 		last->next = new;
// 		// new->next = NULL;
// 	// }
// 	// printf("after appending: %s\n", last->next->args[0]);
// }
// to be tested
// adds a new node to the back of the linked list
void	add_node(t_cmd **list, t_cmd *new)
{
	t_cmd	*current;

	current = *list;
	while (current != NULL && current->next != NULL)
		current = current->next;
	// printf("to add: %s\n", new->args[0]);
	current->next = new;
}

// goes out - only for testing
void	print_list(t_cmd *list)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		printf("i = %i\n", i);
		printf("tadaaaa: %s\n", list->args[0]);
		list = list->next;
		i++;
	}
}

// to be tested
// splits pipeline into cmd-lines, and creates 1 node per cmd-line
// attention: what I need here to be passed is blacked out string!
void	create_cmd_list(char *pipeline, int cmd_count, t_shell *minishell)
{
	char	**arr;
	t_cmd	*list;
	int		i;

	// list = NULL;
	// splits the pipeline into its cmd-lines
	arr = ft_split(pipeline, 124); // works
	// printf("%s\n", arr[0]);
	// printf("%s\n", arr[2]);
	// printf("%s\n", arr[4]);
	// initiates the list, creates first node with entire cmd line
	list = create_node(arr[0]); // works
	i = 0;
	// creates entire list by passing 1 cmd-line per node
	while (++i < cmd_count) // works
	{
		// printf("%i\n", i);
		add_node(&list, create_node(arr[i]));
	}
	// print_list(list);
	// printf("[0]%s\n", list->args[0]);
	// list = list->next;
	// printf("[1]%s\n", list->args[0]);
	// list = list->next;
	// printf("[2]%s\n", list->args[0]);
	minishell->cmd = list;
	// ft_free(arr);
	// return (list);
}

// ----------for testing only-----------------------
int	main(void)
{
	t_shell	minishell;
	t_cmd	*the_list;
	int		pipecount;

	pipecount = 0;
	minishell.pipe_count = 4;
	create_cmd_list("hello | string | another sk8ter | whoop whoop | END", 5, &minishell);
	while (pipecount < 5)
	{
		printf("main| %s\n", minishell.cmd->args[0]);
		pipecount++;
		minishell.cmd = minishell.cmd->next;
	}
}
