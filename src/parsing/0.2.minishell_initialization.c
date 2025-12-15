/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.2.minishell_initialization.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:13:31 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/15 12:00:18 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ---------------  - needs to go out!  --------------
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

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
// ---------------  libft functions - end!  --------------

// works
// sets the prompt, reads the user input and saves it into a char *buffer
// creates and continously adds to history if input is non-empty
int	init_minishell(t_shell *minishell)
{
	const char	*prompt;
	static char	*input_str;

	prompt = ft_strjoin(getenv("USER"), "@minishell: ");
	setup_signals(handle_signal_parent);
	while (1)
	{
		if (input_str)
		{
			free(input_str);
			input_str = NULL;
		}
		input_str = readline(prompt);
		if (!input_str)// exits in case of ctrl-D
		{
			printf("exit\n");
			exit(1);
		}
		if (*input_str)
		{
			parse_pipeline(input_str, minishell); //what if this one fails?
			add_history(input_str);// adds user input to history
		}
	}
	return (0);
}

// only for testing-------------------------------
// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	if (!(init_minishell(env)))
// 		return (printf("Error with initialization.\n"), 1);
// 	return (0);
// }
