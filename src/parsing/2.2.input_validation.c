/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.2.input_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:15:50 by kschmitt          #+#    #+#             */
/*   Updated: 2025/11/26 17:02:12 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STRUCTURE FOR INPUT VALIDATION */

START OF STRING

(0) whitespaces
	- always and at any time loop through whitespaces
	- none of them is to be passed to execution
	- exception: whitespaces within quotes >> need to be handled
		- in argument, env. arg.: passed as part of the argument
		- in command, flags, filename: not ok! >> error (who handles this?)

(0.5) first encounter == quote
	- content of quote needs to be valid command
	- if not: END

(1) check for built-in commands (except for echo) at beginning of string
	- cd >> pass: cmd + string after cmd (should be path), cut off eveything after
	- pwd, export, unset, env, exit >> pass: cmd, cut off everything after
	END

(2) syntax check pipes
	- if not valid: END
	- pass count of cmds in struct t_shell

(3) syntaxt check redirs
	- if not valid: END

_______
SPLIT STRING INTO ARRAY OF STRINGS (DELIMITER = PIPE)
FOR EACH SUBSTRING:

(4) extract redirections
	- syntax check redirs
		- if not valid: END
	- fill and pass: struct t_redirs

(5) check if cmd is valid according to definition in 2.0
	>> if not valid: END
	- if valid:
		- if "echo" >> pass: cmd + flag + array of arguments (redirs are not arg of "echo"!)

(6) flags?

(7) env arg?

(8) arguments belonging to command?

(9) quotes? >> needs to be checked WAY earlier
