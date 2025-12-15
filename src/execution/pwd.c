/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:46:37 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/14 18:42:43 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_shell *shell, t_cmd *cmd)
{
	char	curr_dir[PATH_MAX];

	(void)shell;
	(void)cmd;
	if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
	{
		ft_putstr_fd(curr_dir, 1);
		ft_putstr_fd("\n", 1);
		return (SUCCESS);
	}
	else
		return (perror("pwd"), FAILURE);
}
