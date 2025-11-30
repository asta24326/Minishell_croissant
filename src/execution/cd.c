/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:28:23 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/11/30 22:23:44 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_strjoin_three(char *key, char *value)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (perror("cd: env update failed"), NULL);
	res = ft_strjoin(temp, value);
	if (!res)
		return (perror("cd: env update failed"), NULL);
	free(temp);
	return (res);
}

static int	ft_set_cd_vars(t_shell *shell, char *key, char *value)
{
	char	*new_var;
	int		i;

	new_var = ft_strjoin_three(key, value);
	i = 0;
	while (shell->env[i])// check if variable already exists
	{
		if (ft_strncmp(shell->env[i], key, ft_strlen(key)) == 0
			&& shell->env[i][ft_strlen(key)] == '=') //make sure that it starts with out key fully and closed with "="
		{
			free(shell->env[i]);//free the spot
			shell->env[i] = new_var;
			return (SUCCESS);
		}
		i++;//if it doesn't exist, then we'll reach the very end
	}
	if (ft_create_cd_arg(shell, new_var) == FAILURE)
		return (free(new_var), FAILURE);
	return (SUCCESS);
}

int	ft_create_cd_arg(t_shell *shell, char *new_var)
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

int	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	new_pwd[PATH_MAX];
	char	old_pwd[PATH_MAX];
	char	*target;

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		return (perror("cd: error getting current directory"), FAILURE);
	if (cmd->args[2]) // check if arguments more than 1
		return (perror("cd: too many arguments\n"), FAILURE);
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)//determine home directory
		target = getenv("HOME");
	else if (ft_strcmp(cmd->args[1], "-") == 0)// if "-" means fo back to OLDPWD
		target = getenv("OLDPWD");
	else
		target = cmd->args[1];
	if (!target)
		return (FAILURE);
	if (chdir(target) == -1)// changing target/direction
		return (perror("cd: failed"), FAILURE);
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL) // update PWD
		return (perror("cd: error getting current directory"), FAILURE);
	ft_set_cd_vars(shell, "PWD", new_pwd);// set new_pwd
	ft_set_cd_vars(shell, "OLDPWD", old_pwd);// set old_pwd
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-") == 0)
		printf("%s\n", new_pwd);
	return (SUCCESS);
}
