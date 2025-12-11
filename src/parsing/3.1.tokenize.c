/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.1.tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:33:40 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/10 18:05:50 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// // old version
// // splits cmd_line into its tokens
// void	tokenize(char *cmd_str, t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	// loops through cmd_str and sets i to byte after operator
// 	while (cmd_str[i])
// 	{
// 		if (is_quote(cmd_str[i]))
// 			cmd_str += parse_quote(cmd_str + i, cmd);
// 		if (is_other(cmd_str[i]))
// 			cmd_str += parse_cmd(cmd_str + i, cmd);
// 		// works because at this point, the pipe operators were taken out already
// 		if (is_operator(cmd_str[i]))
// 			cmd_str += parse_redir(cmd_str + i, cmd);
// 		else
// 			cmd_str++;
// 	}
// }

// //OLD
// // works
// // splits cmd_line into its tokens
// void	tokenize(char *cmd_str, t_cmd *cmd)
// {
// 	// loops through cmd_str and sets i to byte after operator
// 	while (*cmd_str)
// 	{
// 		if (is_quote(*cmd_str))
// 			cmd_str += parse_quote(cmd_str, cmd);
// 		else if (is_other(*cmd_str))
// 			cmd_str += parse_cmd(cmd_str, cmd);
// 		// works because at this point, the pipe operators were taken out already
// 		else if (is_operator(*cmd_str))
// 			cmd_str += parse_redir(cmd_str, cmd);
// 		else
// 			cmd_str += 1;
// 	}
// }

// works
// forks tokens into arguments and redirs
void	tokenize(char *cmd_str, t_cmd *cmd)
{
	// loops through cmd_str and sets i to byte after operator
	while (*cmd_str)
	{
		if (is_quote(*cmd_str) || is_other(*cmd_str))
			cmd_str += parse_cmd(cmd_str, cmd);
		// works because at this point, the pipe operators were taken out already
		else if (is_redir(*cmd_str))
			cmd_str += parse_redir(cmd_str, cmd);
		else
			cmd_str += 1;
	}
}
