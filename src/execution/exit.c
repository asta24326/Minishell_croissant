/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:15:04 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/14 22:43:20 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_is_valid_exit_arg(t_shell *shell, t_cmd *cmd);
static bool	ft_is_numeric_str(char *arg);
static long	ft_get_exit_code(char *arg);

int	ft_exit(t_shell *shell, t_cmd *cmd)
{
	long	exit_code;

	(void)shell;
	ft_putstr_fd("exit\n", 2);
	if (!cmd->args[1])
		exit(0);
	if (ft_is_valid_exit_arg(shell, cmd) == false)
	{
		if (cmd->args[2])
			return (FAILURE);
		exit(2);
	}
	exit_code = ft_get_exit_code(cmd->args[1]);
	exit(exit_code);
	return (SUCCESS);
}

static bool	ft_is_valid_exit_arg(t_shell *shell, t_cmd *cmd)
{
	(void)shell;
	
	if (ft_is_numeric_str(cmd->args[1]) == false)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (false);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (false);
	}
	return (true);
}

static bool	ft_is_numeric_str(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (false);
	i = -1;
	if (arg[0] == '+' || arg[0] == '-')
		i++;
	if (!arg[i])
		return (false);
	while (arg[++i])
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
	return (true);
}

static long	ft_get_exit_code(char *arg)
{
	long	l_nbr;
	int		i;
	int		sign;

	l_nbr = 0;
	i = 0;
	sign = 1;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		l_nbr = l_nbr * 10 + (arg[i] - '0');
		i++;
	}
	l_nbr = l_nbr * sign;
	if (l_nbr < 0)
		l_nbr = 256 + (l_nbr % 256);
	else
		l_nbr = l_nbr % 256;
	return ((int)l_nbr);
}
