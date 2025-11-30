/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 22:27:14 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/11/30 23:47:41 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_main_expand_args(t_shell *shell, char **env)
{
	int	exp_var_flag;

	exp_var_flag = 1;
	while (exp_var_flag != 0)
	{
		exp_var_flag = 0;
		ft_expand_args(shell, env, &exp_var_flag);
	}
}

int	ft_expand_args(t_shell *shell, char **env, int	*exp_var_flag)
{
	int		i;
	t_cmd	*curr_cmd;

	curr_cmd = shell->cmd;
	while (curr_cmd)
	{
		i = -1;
		while (curr_cmd->args[++i])
		{
			if (ft_strchr(curr_cmd->args[i], '$'))
			{
				*exp_var_flag = 1;
				if (ft_is_valid_var(env, curr_cmd->args[i]) == false)
					return (FAILURE);
				if (ft_is_exist(env, curr_cmd->args[i]) == true)
					if (ft_expand_var(env, curr_cmd->args[i]) == FAILURE)
						return (FAILURE);
				else
					if (ft_remove_exp_var(env, curr_cmd->args[i]) == FAILURE)
						return (FAILURE);
			}
		}
		curr_cmd = curr_cmd->next;
	}
	return (SUCCESS);
}

bool	ft_is_valid_var(char **env, char *arg)
{
	int		i;
	char	*exp_adr;

	exp_adr = ft_strchr(arg, '$');
	i = exp_adr - arg + 1; // calculate the index where
	if (ft_is_valid_var_name_char(arg[i]))
	{
		if(arg[i + 1] == '\0')
			return (true);
		i++;
	}
	while (ft_is_valid_export_name_char(arg[i])
			|| (arg[i] >= '0' && arg[i] <= '9'))
	{
		if (arg[i + 1] == '\0' || arg[i + 1] == '=')
			return (true);
		i++;
	}
	return (perror("invalid var name"), false);
}

static bool	ft_is_valid_var_name_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		 || (c == '_'))
		 return (true);
	return (false);
}

static size_t	ft_exp_var_len(char *var)
{
	int		i;
	size_t	var_len;

	var_len = 0;
	i = -1;
	while (var[++i] && var[i])
	{
		
	}
	return (var_len);
}

static bool	ft_var_is_exist(char **env, char *var)
{
	int		i;

	i = -1;
	while (env[++i])// check if variable already exists
	{
		if (ft_strncmp(env[i], new_var, ft_varlen(new_var)) == 0
			&& shell->env[i][ft_keylen(new_var)] == '=') //make sure that it starts with out key fully and closed with "="
		{
			free(shell->env[i]);//free the spot
			shell->env[i] = new_var;
			return (SUCCESS);
		}
	}
	
	return (false);
}