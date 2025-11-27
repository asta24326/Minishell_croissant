/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.0.syntax_def_&_rules.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:54:27 by kschmitt          #+#    #+#             */
/*   Updated: 2025/11/27 12:18:31 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DEFINITIONS */

input string
	- entire string returned by readline (= user input)

command string
	- string enclosed by start/end of input string OR by pipe(s)
	- holds exactly 1 command
	- can additionally include flags, arguments and redirections

invalid cmd string
	- contains only whitespaces
	- contains only tokens (<|>)
	- contains only '$'/ $XXX
	// - contains free floating quotes (single or double)
	// - contains a redirection (<>) without filename
	// - contains an append (>>) without filename
	// - contains heredoc (<<) without delimiter
	- contains anything of the above in combination
	- contains digits

valid cmd string
	- contains >= 1 valid cmd which is not
		a) whitespace
		b) token
		c) '$' / $XXX
		d) quotes
	// - contains filename for redirection/append
	// - contains delimiter for heredoc
	- OR contains valid redirection

valid cmd
	- contains non-digit characters
	-


valid pipe
	- is a single pipe token
	- contains valid cmd on left side
	- contains valid cmd on right side
	- is not in quotes

valid redirection
	- is 1 or 2 redir tokens
	- is FOLLOWED by filename or in case of heredoc by delimiter
	- can stand solo (without command)
		'>' empties file
		'<' does nothing >> no need to pass probably
		'<<' opens heredoc
		'>>' does nothing >> no need to pass probably
	- is not in quotes

valid quotes
	- everything seems valid, haha


/* RULES */

input string
	- if cmd cannot work with output of prev cmd passed by pipe, stdout is simply overwritten (execution)
	- if one command string has error
		- error is redirected to fd2
		- pipe continues with fd1 being empty

pipe [|]
	(0) amount
		- should be exactly 1 >> else syntax error (in our version)
	(1) cmd BEFORE
	- needs valid cmd BEFORE >> if !cmd: syntax error
	- counts for every pipe in input line
		> first check: do all pipes have a cmd before?
	if (1): (2) cmd AFTER
	- if !(cmd AFTER)
		- opens a new readline with "> ", looks like heredoc but ends after ENTER is pressed
		- takes this user input as the second command
		- saved in history as ONE command line

redirection [<>] in 1 cmd
	(1) amount
		- needs to be exactly 1 (< >) or 2 (<< >>)
		- if >2: syntax error
	(2) filename
		- needs filename for <, >, >>
		- if !filename: syntaxt error
	(3) delimiter
		- needs delimiter for << (heredoc)
		- if !delimiter: syntaxt error
	(4) multiple redirs of same sort (true for all 4)
		- if multiple redirs of same sort, the most right one is boss, all others are simply created empty
	(5) multiple redirs of diff sort, same direction
		- '>' rules over '>>' (only '>' is processed, no matter the order)
		- '<<' rules over '<' (only '<<' is processed, no matter the order)
	(6) multiple redirs of diff sort, diff direction
		- for ('<' or '<<') and ('>' or '>>'), order doesnt matter (work as intended)

quotes ["" '']
	(0) combination needed
		- quotes cannot be free-floating, meaning they need to follow on e.g. echo, else: syntax error
	(1) case non-closed (only 1 quotation mark)
		- opens heredoc(?) with pairing quotation mark as delimiter, allows to include '\n'
	(2) quote in quote with diff quotes (eg. "'hello'")
		- outer quote is only one handled as quote
		- inner quotation marks are taken as char
	(3) quote in quote with same quotes (eg. ""hello"")
		- outer quotes are taken, inner ones are ignored
	(4) env arg >> needs indication/differentiation for execv
		- "$XX" passes the env. argument
		- '$XX' passes a literal string
	(5) content
		-if nothing in between quotes >> quotes are entirely ignored
	(6) syntax
		- searches for next matching quotation mark and takes it as end of quote

quotes at start of command string
	- bash expects a command inside quotes > NEEDS to be a command
	- if no command > syntaxt error

quotes on built-in commands
	- can be in quotes, but then it has to be EXACTLY the command (no whitespaces, no arguments)
	- for cd: path can be in quotes too, also needs to be EXACT (no whitespaces)

quotes on simple commands
	- can be in quotes, but then it has to be EXACTLY the command (no whitespaces, no arguments)

quotes on commands taking several arguments (e.g. cat, echo)
	- can be in quotes, but then it has to be EXACTLY the command (no whitespaces, no arguments)
	- arguments
		- filename can be in quotes too, also needs to be EXACT (no whitespaces)
		- other arguments can be in quotes too

quotes on commands followed by a flag (eg. ls -a)
	- can be in quotes, but then it has to be EXACTLY the command (no whitespaces, no arguments)
	- flag can be in quotes too, also needs to be EXACT (no whitespaces)

quotes around tokens
	pipe
		- then considered as argument to command
	redirections
		- at start of cmd str: then considered as cmd > error
		- at end of cmd str: then considered as argument to command
		-filename can be in quotes too, also needs to be EXACT (no whitespaces)
		-quoted deliminter pass env. arg as literal string, not as env. var.!

quotes on to be created filenames (> and >>)
	- filenames include quotes and all whitespaces within quote

quotes on env. arg. ($)
	- quotes around $ only
		- treates as two separate arguments > passes it literally (e.g. $USER)
	- quotes around entire argument
		- single quotes pass argument literally (e.g. $USER)
		- double quotes pass env. arg


/* BUILT-IN COMMANDS */

echo
	- check that it is EXACTLY "cd" (no syntax error)
	(0) check for '-n' (use flag) >> leaves out LAST '\n'
	(1) input
		- takes all arguments following "echo"
		- except for tokens if they are valid
		- is delimited by null-terminator or pipe
		- ignores whitespaces, empty quotes
		- takes env. var ($) and prints translated version
		- takes quoted arguments in between unquoted arguments
	(2) output
		- all arguments
		- empty line in case of no, empty or non-valid (e.g. $PC) arguments
	>>passed with '-n' flag and array of arguments

cd (with options)
	- check that it is EXACTLY "cd" (no syntax error)
	>>passed entirely & handled in execution

pwd, export, unset, env, exit (no options)
	- check that it is EXACTLY the command (no syntax error)
	>>passed without anything coming after (cut out in parsing)

