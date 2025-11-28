/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.3.parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:18:34 by kschmitt          #+#    #+#             */
/*   Updated: 2025/11/28 18:11:04 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TO BE REDONE! >> all passed by struct
// checks whether cmd is built-in command
// sends it directly to execution (except for echo and cd)
// int	is_builtin_cmd(char *str)
// {
// 	// returns 2 (as flag if you want) to indicate that those commands will be passed through struct
// 	if (!(ft_strncmp(str, "echo", ft_strlen(str)))
// 		|| !(ft_strncmp(str, "cd", ft_strlen(str))))
// 		return (2);
// 	else if (!(ft_strncmp(str, "pwd", ft_strlen(str))))
// 		exec_pwd();
// 	else if (!(ft_strncmp(str, "export", ft_strlen(str))))
// 		exec_export();
// 	else if (!(ft_strncmp(str, "unset", ft_strlen(str))))
// 		exec_unset();
// 	else if (!(ft_strncmp(str, "env", ft_strlen(str))))
// 		exec_env();
// 	else if (!(ft_strncmp(str, "exit", ft_strlen(str))))
// 		exec_exit();
// 	else
// 		return (0);
// 	return (1);
// }

// to be discussed
// checks whether cmd is built-in command, nothing else needs to be passed here
int	is_stand_alone_builtin_cmd(char *str)
{
	if (!(ft_strncmp(str, "pwd", ft_strlen(str))))
		return (1);
	else if (!(ft_strncmp(str, "export", ft_strlen(str))))
		return (1);
	else if (!(ft_strncmp(str, "unset", ft_strlen(str))))
		return (1);
	else if (!(ft_strncmp(str, "env", ft_strlen(str))))
		return (1);
	else if (!(ft_strncmp(str, "exit", ft_strlen(str))))
		return (1);
	return (0);
}

// works
// takes the current byte at which we stopped and looks into the following one(s)
// returns the next non-whitespace character
// does not change the pointer position of source str
char	sneak_preview(char *str)
{
	printf("arrived: %s\n", str);
	while (*str)
	{
		str++;
		if (!(is_whitespace(*str)))
			return (*str);
	}
	return (0);
}


void	parse(char *input_str, t_shell *minishell, char **env)
{
	//syntax_check
	if (!(is_valid_syntax(input_str)))
		ft_printf("Syntax error.\n");
	//list_creation
	//parsing
}
