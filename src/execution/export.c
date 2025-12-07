/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:29:54 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/07 20:06:40 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
	What export does:
	- Sets environment variables for the current shell and child processes
	- Without arguments: Prints all exported variables
	- With arguments: Sets variables in format NAME=value
*/

static int		ft_set_var(t_shell *shell, char *var);
static int		ft_add_new_var(t_shell *shell, char *var);
static void		ft_print_all(char **env);
static bool		ft_is_valid_var_name(char *var);

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int		i;

	if (!cmd->args[1] || !cmd->args[1][0])
		ft_print_all(shell->env);
	i = 0;
	while (cmd->args[++i])
	{
		if (ft_is_valid_var_name(cmd->args[i]) == false) //check name of arg
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (FAILURE);
		}
		if (ft_set_var(shell, cmd->args[i]))
			return (perror("set env var failed"), FAILURE);
	}
	return (SUCCESS);
}

static int	ft_set_var(t_shell *shell, char *var)
{
	int		i;
	size_t	var_len;

	i = -1;
	var_len = ft_var_name_len(var);
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], var, var_len) == 0
			&& shell->env[i][var_len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(var);
			if (!shell->env[i])
				return (FAILURE);
			return (SUCCESS);
		}
	}
	if (ft_add_new_var(shell, ft_strdup(var)) == SUCCESS)
		return (SUCCESS);
	else
		return (FAILURE);
}

static int	ft_add_new_var(t_shell *shell, char *var)
{
	char	**new_env_arr;
	int		env_len;
	int		i;

	if (!var)
		return (FAILURE);
	env_len = 0;
	while (shell->env[env_len])
		env_len++;
	new_env_arr = malloc (sizeof(char *) * (env_len + 2));
	if (!new_env_arr)
		return (free(var), FAILURE);
	i = -1;
	while (shell->env[++i])
		new_env_arr[i] = shell->env[i];
	new_env_arr[i] = var;
	new_env_arr[i + 1] = NULL;
	ft_free_arr_str(shell->env);
	shell->env = new_env_arr;
	return (SUCCESS);
}

static void	ft_print_all(char **env)
{
	int	i;

	if (!env || !env[0])
		return ;
	i = -1;
	while (env[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
	}
}

static bool	ft_is_valid_var_name(char *var)
{
	size_t	i;
	size_t	var_name_len;

	if (!var || !var[0])
		return (false);
	var_name_len = ft_get_var_name_len(var);
	if (var[0] != '_' && !ft_isalpha(var[0])) //first char: letter or underscore
		return (false);
	i = 0;
	while (++i < var_name_len) //cheking the rest of the vars in name
		if (var[i] != '_' && !ft_isalnum(var[i]))
			return (false);
	return (true);
}
