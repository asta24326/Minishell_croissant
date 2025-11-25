/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:29:52 by kschmitt          #+#    #+#             */
/*   Updated: 2025/11/25 23:07:43 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* MACROS */

# define SUCCESS 0
# define FAILURE 1

/* LIBRARIES */

# include "../libraries/libft/libft.h"

/* HEADERS */

// for readline and all rl_* functions:
# include <readline/readline.h>
# include <readline/history.h>

// for printf, readline
# include <stdio.h>

// for malloc, free, getenv
# include <stdlib.h>

// for access, getcwd, chdir, unlink, execve,
// dup, dup2, pipe, isatty, ttyname, ttyslot
# include <unistd.h>

// for write, open, read, close, unlink
# include <fcntl.h>

// for error handling
# include <errno.h>

// for fork, stat, lstat, fstat, opendir
# include <sys/types.h>

// for wait, waitpid
# include <sys/wait.h>

// for wait3, wait4
# include <sys/time.h>
# include <sys/resource.h>

// for signal, sigaction, etc.
# include <signal.h>

// for stat, lstat, fstat
# include <sys/stat.h>

// for opendir, readdir, closedir
# include <dirent.h>

// for strerror
# include <string.h>

// for ioctl
# include <sys/ioctl.h>

// for tcsetattr, tcgetattr
# include <termios.h>

// for tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>

// for tputs
# include <term.h>

// for boolean expressions
# include <stdbool.h>


/* STRUCTURES */

/* redirections struct */
typedef struct	s_redirs
{
	int		in_fd;
	int		out_fd;
	bool	append;
	bool	exp_hdoc; // if heredoc delimeter has '  ' 
	int		hdoc_fd[2]; // on exec step
}	t_redirs;

/* command data structure */
typedef struct	s_cmd
{
	char 		*name;
	char		**args;
	char		*infile;
	char		*outfile;
	char		*hdoc_delim;
	t_redirs	*redirs;
	t_cmd		*next;
}	t_cmd;

/* main data storage */
typedef struct	s_shell
{
	int		cmds_count;
	int		**pipes;
	char	**env;
	t_cmd	*cmd;
}	t_shell;

#endif
