/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:48:00 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/10 19:49:16 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_sort_algo(int count, char **sorted);

char	**ft_sort_env(char **env)
{
	char	**sorted;
	int		count;
	int		i;

	count = 0;
	while (env[count])
		count++;
	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		sorted[i] = ft_strdup(env[i]);
		if (!sorted[i])
		{
			while (--i >= 0)
				free(sorted[i]);
			free(sorted);
			return (NULL);
		}
	}
	sorted[count] = NULL;
	ft_sort_algo(count, sorted);
	return (sorted);
}

static void	ft_sort_algo(int count, char **sorted)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < count - 1)
	{
		j = i;
		while (++j < count)
		{
			if (ft_strcmp(sorted[i], sorted[j]) > 0)
			{
				temp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = temp;
			}
		}
	}
}