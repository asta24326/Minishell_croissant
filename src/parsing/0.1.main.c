/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:34:19 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 14:24:08 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	*minishell;

	(void)ac;
	(void)av;
	minishell = (t_shell *)malloc(sizeof(t_shell));
	if (!minishell)
		return (perror("t_shell memory allocation"), FAILURE);
	minishell->env = ft_env_dup(env);
	if (!minishell->env)
		return (free(minishell), FAILURE);
	init_minishell(minishell);
	end_minishell(minishell);
	return (SUCCESS);
}
