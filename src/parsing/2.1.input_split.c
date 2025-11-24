/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.1.input_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:17:09 by kschmitt          #+#    #+#             */
/*   Updated: 2025/11/24 18:05:46 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ---------------  libft functions - need to go out!  --------------
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

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
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
// ---------------  libft functions - end!  --------------

// typedef struct s_data
// {
// 	int		cmds_count;
// 	int		**pipes;
// 	t_cmd	*init_cmd;
// }	t_data;

// works
// returns the # of cmds passed
int	get_cmds_count(char **arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arr[i] != NULL)
	{
		count++;
		i++;
	}
	return (count);
}

//works
//separates the cmds and sets the cmds_count;
void	separate_cmds(t_data *minishell, char *str)
{
	char	**cmd_arr;
	int		cmds;

	cmd_arr = ft_split(str, 124);
	minishell->cmds_count = get_cmds_count(cmd_arr);
}


int	main(void)
{
	t_data	minishell;
	char	*input;

	minishell.cmds_count = 0;
	printf("%i\n", minishell.cmds_count);
	input = "echo hi ha ho >file1 | echo hello | wc -l";
	separate_cmds(&minishell, input);
	printf("%i\n", minishell.cmds_count);
}
