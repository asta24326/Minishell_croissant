/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:31:01 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/14 21:33:02 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_get_var_name_len(char *arg)
{
	size_t	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (len);
}

char	*ft_expand_env_var(t_shell *shell, char *arg)
{
	int		i;
	size_t	var_name_len;
	char	*result;

	var_name_len = ft_get_var_name_len(arg + 1);
	i = -1;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], arg + 1, var_name_len) == 0
			&& shell->env[i][var_name_len] == '=')
		{
			result = ft_strdup(ft_strchr(shell->env[i], '=') + 1);
			return (result);
		}
	}
	return (ft_strdup(""));
}
