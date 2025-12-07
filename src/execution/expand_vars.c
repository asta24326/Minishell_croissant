/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 22:27:14 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/07 20:05:42 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_is_valid_var_char(int c);

int	ft_expand_all_args(t_shell *shell)// main function to expand variables in all commands
{
	t_cmd	*curr_cmd;
	int		i;
	char	*expanded;

	curr_cmd = shell->cmd;
	while (curr_cmd)
	{
		i = -1;
		while (curr_cmd->args && curr_cmd->args[++i])// got through every coommand in list
		{
			expanded = ft_expand_arg(shell, curr_cmd->args[i]);
			if (!expanded)
				return (FAILURE);
			free(curr_cmd->args[i]);
			curr_cmd->args[i] = expanded;// adding expanded string
		}
		curr_cmd = curr_cmd->next;
	}
	return (SUCCESS);
}

char	*ft_expand_arg(t_shell *shell, char *arg)
{
	if (!arg)
		return (NULL);
	if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')//case if there is ' '
		return (ft_substr(arg, 1, ft_strlen(arg) - 2));// simply returning string
	if (arg[0] == '$')
	{
		if (arg[1] == '?')
			return (ft_itoa(shell->exit_status));
		if (arg[1] == '$')
			return (ft_itoa(shell->shell_pid));
		if (arg[1] && ft_is_valid_var_char(arg[1]) == true)
			return (ft_expand_env_var(shell, arg));
		return (ft_strdup(arg));
	}
	return (ft_strdup(arg));
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

size_t	ft_get_var_name_len(char *arg)
{
	size_t	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (len);
}

static bool	ft_is_valid_var_char(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}
