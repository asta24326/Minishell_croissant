/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.2.parse_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:35:55 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/04 13:20:20 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ------------needs to go out---------------------
// size_t	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (*s++)
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(const char *s)
// {
// 	size_t	s_len;
// 	char	*dest;
// 	size_t	i;

// 	i = 0;
// 	s_len = ft_strlen(s);
// 	dest = (char *)malloc(sizeof(char) * (s_len + 1));
// 	if (dest == NULL)
// 		return (NULL);
// 	while (s_len > i)
// 	{
// 		dest[i] = s[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*dest;
// 	size_t	str_len;
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	str_len = ft_strlen(s);
// 	if (start >= str_len)
// 		return (ft_strdup(""));
// 	if (len > str_len - start)
// 		len = str_len - start;
// 	dest = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!dest)
// 		return (NULL);
// 	i = 0;
// 	while (len > i)
// 	{
// 		dest[i] = s[start + i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }
// ------------END (needs to go out)---------------------

// works
// attention: so far not conisdered: open quotation marks
// returns the str length of the quote that has to be passed to parse_cmd
int	get_quot_len(char *str, char quot_mark, int *env_arg)
{
	int	len;

	len = 0;
	// skip first quotation mark
	str++;
	while (*str && *str != quot_mark)
	{
		len++;
		// if dollar is encountered, env_arg is "tunred off"
		if (*str == 36)
			*env_arg = 0;
		str++;
	}
	// adds two bytes in case of single quotation marks in combination with dollar sign to include quotation marks into string
	if (quot_mark == 39 && *env_arg == 0)
		len += 2;
	return (len);
}

// works
// attention: so far not conisdered: open quotation marks
// loops through quotation and returns index after quote
int	parse_quote(char *str, t_cmd *cmd)
{
	int		env_arg;
	int		index;
	char	*quot;

	env_arg = 1; //true by default
	index = get_quot_len(str, *str, &env_arg);
	quot = ft_substr(str, env_arg, index);		//attention: memory allocation
	fill_args_arr(quot, cmd);
	// add 2 bytes for 2 quotation marks
	if (*str == 34 || (*str == 39 && env_arg == 1))
		index += 2;
	return (index);
}
