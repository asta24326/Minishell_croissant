/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 19:39:10 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/07 19:45:20 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_env_dup(char **env)
{
	char	**new_env;
	int		i;
	int		count;

	count = -1;
	while (env[++count]);//calculationg current env strings
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (perror("env_init malloc failed"), NULL);
	i = -1;
	while (++i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)// cleanup in case of fail
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
	}
	new_env[count] = NULL;
	return (new_env);
}
