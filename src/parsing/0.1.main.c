/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.1.main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:34:19 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/04 18:29:58 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Structure logic
// 0.x. overall
// 1.x. pipeline level
// 2.x. command string level
// 3.x. argument level

// works
int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (!init_minishell(env))
		return (ft_printf("Error with initialization.\n"), 1);
	return (0);
}
