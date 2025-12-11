/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.3.parse_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:18:25 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/10 18:08:00 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// int	is_quote(char c)
// {
// 	if (c == 34 || c == 39)
// 		return (1);
// 	return (0);
// }

// int	is_operator(char c)
// {
// 	if (c == 124 || c == 60 || c == 62)
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

// - get sign
// - get filename/redir
// -

// status in program when starting to parse redirs:
// 	- quotes are blacked out
// 	- ensured that filename/delimiter are there (so correct syntax)
// 	- pipes are excluded, we look at cmd line

//works
// str needs to be blacked out
int	get_redir_count(char *cmd_str)
{
	char	*copy;
	int		i;
	int		count;

	copy = blackout_quoted_content(cmd_str);
	i = 0;
	count = 0;
	while (copy[i])
	{
		// works because pipes have been taken out and quotes are blacked out
		if (is_operator(copy[i]))
		{
			count++;
			i++;
			if (is_operator(copy[i]))
				i++;
		}
		i++;
	}
	free (copy);
	return (count);
}

// WIP
int	get_redir_type(char *cmd_str)
{

}

// for testing only
int	main(void)
{
	// char	*cmd_str;
	// char	*redir_sign;
	// char	*file_delim;
	// int		i;

	printf("redir count = %i\n", get_redir_count("<<hello >>whoop >jou <Xmas!"));
	// parse_redir("hellloooo 'hey' oooops' where?'");
	// i = -1;
	// while (++i < 4)
	// 	printf("arr[%i]: %s\n", i, arr[i]);
	return (0);
}


// typedef struct	s_redirs
// {
// 	int		in_fd;
// 	int		out_fd;
// 	char	*hdoc_delim;
// 	bool	exp_hdoc; // no - if heredoc delimeter has '  ', yes - if none
// 	int		hdoc_fd[2]; // on exec step
// }	t_redirs;


t_redirs	*extract_redir_data(char *cmd_line)
{
	t_redirs	*redirs;

	redirs = (t_redirs *)malloc(sizeof(t_redirs));
	if (!redirs)
		return (printf("Memory allocation failed.\n"), NULL);
	in_fd =
	out_fd =
	hdoc_delim =
	exp_hdoc =
	hdoc_fd = NULL; //handled in exec
	return (redirs);
}

// works
// handles the redir depending on the type
void	handle_redir(char *str, t_cmd *cmd)
{
	if (str[0] == '>' && str[1] != '>')
		printf("outfile!\n");
	else if (str[0] == '>' && str[1] == '>')
		printf("append\n");
	else if (str[0] == '<' && str[1] != '<')
		printf("infile\n");
	else if (str[0] == '<' && str[1] == '<')
		printf("heredoc\n"); //done by Aidar
}

// works
// returns length of redirection token
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

// here, we look into single redirs
// returns index after the redir token
int	parse_redir(char *str, t_cmd *cmd)
{
	int	index;

	index = get_redir_len(str);
	handle_redir(str, cmd);
	return (index);
}
