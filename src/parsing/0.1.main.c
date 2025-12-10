/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.1.main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:34:19 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/10 18:34:14 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Structure logic
// 0.x. overall
// 1.x. pipeline level (input str)
// 2.x. command string level (input str split by pipes)
// 3.x. token level (arg vs. redir)
// 4.x. argument level (cmd, built-in cmd, flag, arg, env. arg, quotes)

// works
int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	(void)ac;
	(void)av;

	shell = malloc(sizeof(t_shell));
	shell->env = ft_env_dup(env);
	if (!init_minishell(env))
		return (printf("Error with initialization.\n"), 1);
	return (0);
}
