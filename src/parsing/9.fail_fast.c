/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9.fail_fast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:33:56 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/15 11:58:58 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// #include <readline/readline.h>
// #include <readline/history.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

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

char	*ft_strdup(const char *s)
{
	int		i;
	char	*d;

	i = 0;
	d = malloc(strlen(s) + 1);
	if (!d)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	const char	*ptr;

	ptr = src;
	if (size == 0)
		return (strlen(src));
	if (size != 0)
	{
		while (size > 1 && *src)
		{
			*dest++ = *src++;
			size--;
		}
		*dest = '\0';
	}
	return (strlen(ptr));
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	max;

	if (!s)
		return (NULL);
	max = strlen(s);
	if ((start >= max) || len == 0)
		return (ft_strdup(""));
	if (len > (size_t)strlen(s + start))
		len = (size_t)strlen(s + start);
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	s += start;
	if (start < max)
		ft_strlcpy(sub, s, len + 1);
	return (sub);
}
// ---------------  libft functions - end!  --------------

// works
// handles ctrl c in parent process (displays a new prompt on a new line)
void	handle_signal_parent(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();//updates about jump to next line
	// rl_replace_line("", 0);//clears current buffer
	rl_redisplay();//refreshes readline prompt
	return ;
}

void	setup_signals(void (*signal_handler)(int))
{
	signal(SIGINT, signal_handler); //case: ctrl-C
	signal(SIGQUIT, SIG_IGN); //case: ctrl-\ - is ignored
}

// works
// returns the entire prompt for the shell to ask for user input (e.g. kschmitt@c4b10c4:~$ )
// const char	*get_prompt(void) //maybe needs to go into shell struct, otherwise, freeing is complicated
// {
// 	char		*first_part;
// 	char		*sec_part;
// 	const char	*prompt;

// 	first_part = ft_strjoin(getenv("USER"), "@");
// 	sec_part = ft_strjoin(ft_substr(getenv("SESSION_MANAGER"), 6, 7), ":~$ ");
// 	prompt = ft_strjoin(first_part, sec_part); //attention: memory allocation
// 	free(first_part);
// 	free(sec_part);
// 	return (prompt);
// }

// works
// sets the prompt, reads the user input and saves it into a char *buffer
// creates and continously adds to history if input is non-empty
int	init_minishell(t_shell *minishell)
{
	static char	*input_str;
	const char	*prompt;

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
			// parse_pipeline(input_str, minishell); //what if this one fails?
			add_history(input_str);// adds user input to history
		}
	}
	return (0);
}


int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	(void)ac;
	(void)av;

	shell = malloc(sizeof(t_shell));
	// shell->env = ft_env_dup(env);
	shell->env = NULL;
	if (!init_minishell(shell))
		return (printf("Error with initialization.\n"), 1);
	return (0);
}
