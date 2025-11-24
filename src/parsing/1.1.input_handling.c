/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.1.input_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:52:45 by kschmitt          #+#    #+#             */
/*   Updated: 2025/11/24 17:58:42 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ---------------  libft functions - need to go out!  --------------
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
// returns the ID of the corresponding computer for the shell prompt (e.g. c4b10c4)
char	*get_pc_id(void)
{
	char	*session;
	char	*pc_id;

	session = getenv("SESSION_MANAGER");
	pc_id = ft_substr(session, 6, 7);		//attention: hard-coded, to be tested
	return (pc_id);
}

// works
// returns the entire prompt for the shell to ask for user input (e.g. kschmitt@c4b10c4:~$ )
const char	*get_prompt(void)
{
	char		*user;
	char		*pc_id;
	const char	*prompt;

	user = getenv("USER");
	pc_id = get_pc_id();
	prompt = ft_strjoin(user, "@");			//attention: memory allocation
	prompt = ft_strjoin(prompt, pc_id);		//attention: memory allocation
	prompt = ft_strjoin(prompt, ":~$ ");	//attention: memory allocation
	return (prompt);
}

// works
// sets the prompt, reads the user input and saves it into a char *buffer
// creates and continously adds to history if input is non-empty
char	*get_user_input(char *prompt)
{
	if (prompt)
	{
		free(prompt);
		prompt = NULL;
	}
	prompt = readline(get_prompt());
// adds the prompt to the history (attention, history needs to be freed at end of program runtime)
	if (prompt && *prompt)
		add_history(prompt);
	return (prompt);
}

// input handling - for testing
int	main(void)
{
	static char	*prompt;

	prompt = NULL;
	while (1)
	{
		prompt = get_user_input(prompt);
		if (*prompt)
			printf("%s\n", prompt);		//currently: simple echoing
	}
	return (0);
}
