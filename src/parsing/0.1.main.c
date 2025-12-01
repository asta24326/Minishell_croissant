/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.1.main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:34:19 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/01 17:46:50 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;									//alternative: check if ac == 1, else error
	(void)av;									//program name needed?
	if (!init_minishell(env))
		return (ft_printf("Error with initialization.\n"), 1);
	// if (!parsing(&minishell))
	// 	return (ft_printf("Syntax error.\n"), 1);
	// executing(&minishell);
	return (0);
}
