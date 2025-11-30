/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:29:54 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/11/30 23:18:45 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	What export does:
	- Sets environment variables for the current shell and child processes
	- Without arguments: Prints all exported variables
	- With arguments: Sets variables in format NAME=value
*/

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	*expand_var;
	
	if (!cmd->args[1] || !cmd->args[1][0])
		ft_print_env(shell->env);
	i = 0;
	while (cmd->args[++i])
	{
		expand_var = ft_expand_vars(cmd->args[i], shell);
		if (ft_is_valid_var(cmd->args[i]) == false)//check name of arg
			return (FAILURE);
		if (ft_set_export_var(shell, cmd->args[i]))
			return (perror("set env var failed"), FAILURE);
	}
	return (SUCCESS);
}

static int	ft_set_export_var(t_shell *shell, char *new_var)
{
	int		i;
	char	*upd_var;

	i = -1;
	while (shell->env[++i])// check if variable already exists
	{
		if (ft_strncmp(shell->env[i], new_var, ft_keylen(new_var)) == 0
			&& shell->env[i][ft_keylen(new_var)] == '=') //make sure that it starts with out key fully and closed with "="
		{
			free(shell->env[i]);//free the spot
			shell->env[i] = new_var;
			return (SUCCESS);
		}
	}
	if (ft_strchr(new_var, '=') == NULL)// checking if it ends with '='
	{
		upd_var = ft_prep_export_var(new_var);
		if (upd_var == NULL)
			return (FAILURE);
		if (ft_create_export_arg(shell, upd_var) == FAILURE)
			return (FAILURE);
	}
	else if (ft_create_export_arg(shell, new_var) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

static char *ft_prep_export_var(char *old_var)
{
	int		i;
	char	*new_var;

	new_var = malloc(sizeof(char) * (ft_strlen(old_var) + 2));
	if (!new_var)
		return (perror("export: malloc failed"), NULL);
	i = -1;
	while (old_var[++i])
		new_var[i] = old_var[i];
	new_var[i] = '=';
	new_var[i + 1] = '\0';
	return (new_var);
}

int	ft_create_export_arg(t_shell *shell, char *new_var)
{
	char	**new_env;
	int		env_len;
	int		i;

	env_len = 0;
	while (shell->env[env_len])
		env_len++;
	new_env = malloc(sizeof(char *) * (env_len + 2));// to add new_var and NULL
	if (!new_env)
		return (FAILURE);
	i = -1;
	while (shell->env[++i])
		new_env[i] = shell->env[i];// copy old env vars
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (SUCCESS);
}

static void	ft_print_env(char **env)
{
	int	i;
	int	last_arg;

	if (!env || !env[0] || !env[0][0])
		return ;
	i = -1;
	while (env[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
	}
}

static size_t	ft_keylen(char *arg)
{
	size_t	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (len);
}
