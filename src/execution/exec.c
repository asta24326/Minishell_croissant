/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:15:52 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/11/23 23:36:00 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Expecting "t_data *shell, char **env" */

void	ft_exec_init(t_data *shell, char **env)
{
	ft_pipes_init(shell);
	

}


// initialisation of pipes

int	ft_pipes_init(t_data *shell)
{
	int	pipes_count;
	int	i;

	pipes_count = shell->cmds_count - 1;
	if (pipes_count <= 0)
		return (SUCCESS);

	shell->pipes = malloc(sizeof(int *) * pipes_count);
	if (!shell->pipes)
		return (FAILURE);
	
	i = 0;
	while ( i < pipes_count)
	{
		shell->pipes[i] = malloc(sizeof(int) * 2);
		if (!shell->pipes[i])
			return (FAILURE);

		if (pipe(shell->pipes[i]) == -1)
			return (perror("pipe failed"), FAILURE);
		i++;
	}
	return (SUCCESS);
}

// to find check the path and command existance and prepare path for execve
char	*ft_getpath(char *cmd, char **env)
{
	char	**allpaths;
	char	*path_prep;
	char	*exec_str;
	int		i;

	allpaths = ft_split(ft_parse_env("PATH", env), ':');
	if (!allpaths)
		return (NULL);
	i = -1;
	while (allpaths[++i])
	{
		path_prep = ft_strjoin(allpaths[i], "/");
		exec_str = ft_strjoin(path_prep, cmd);
		free (path_prep);
		if (access(exec_str, F_OK | X_OK) == 0)
			return (ft_free_arr(allpaths), exec_str);
		free (exec_str);
	}
	return (ft_free_arr(allpaths), NULL);
}

char	*ft_parse_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*substr;

	if (!name || !env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		substr = ft_substr(env[i], 0, j);
		if (!substr)
			return (NULL);
		if ((ft_strcmp(substr, name)) == 0)
		{
			free(substr);
			return (&env[i][j + 1]);
		}
		free(substr);
	}
	return (NULL);
}
