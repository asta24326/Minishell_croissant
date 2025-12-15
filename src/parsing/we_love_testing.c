/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_love_testing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:17:42 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/11 19:47:10 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

int	is_redir(char c)
{
	if (c == 60 || c == 62)
		return (1);
	return (0);
}

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

// char	*get_filename(char *str, int len)
// {
// 	int	i;
// 	int	ops;
// 	int	whitespaces;

// 	i = -1;
// 	ops = 0;
// 	whitespaces = 0;
// 	while (is_redir(str[++i]))
// 		ops += 1;
// 	while (is_whitespace(str[++i - 1]))
// 		whitespaces += 1;
// 	return (ft_substr(str, ops + whitespaces, len - ops - whitespaces));
// }

char	*get_filename(char *str, int len, int ops)
{
	int	i;
	int	whitespaces;

	i = ops -1;
	whitespaces = 0;
	while (is_whitespace(str[++i]))
		whitespaces += 1;
	return (ft_substr(str, ops + whitespaces, len - ops - whitespaces));
}

int	main(void)
{
	char	*str;

	str = ">>>>>>hey";
	printf("%s\n", get_filename(str, strlen(str), 6));
}
