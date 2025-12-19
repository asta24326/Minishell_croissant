/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:57:12 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/14 18:37:50 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_shell *shell, t_cmd *cmd)
{
	int	i;

	(void)cmd;

	if (!shell->env)
		return (FAILURE);
	i = -1;
	while (shell->env[++i])
	{
		if (ft_strchr(shell->env[i], '='))
		{
				ft_putstr_fd(shell->env[i], 1);
				ft_putstr_fd("\n", 1);
		}
	}
	return (SUCCESS);
}
