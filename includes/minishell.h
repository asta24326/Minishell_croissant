/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:29:52 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/02 16:13:03 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* MACROS */

# define SUCCESS 0
# define FAILURE 1
# define PATH_MAX 1024

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
	bool	exp_hdoc; // no - if heredoc delimeter has '  ', yes - if none
	int		hdoc_fd[2]; // on exec step
	char	*hdoc_delim;
}	t_redirs;

/* command data structure */
typedef struct	s_cmd
{
//	char			*name - no need anymore
	char			**args;
	// char			*infile;
	// char			*outfile;
	char			*hdoc_delim;
	bool			closed; // false if further input is needed through interaction
	bool			builtin;// true if is builtin command
	t_redirs		*redirs;
	struct s_cmd	*next;
}	t_cmd;

/* main data storage */
typedef struct	s_shell
{
	int		pipe_count;
	int		**pipes;
	char	**env;
	t_cmd	*cmd;
	int		exit_status;
}	t_shell;

/* FUNCTIONS */
/* execution folder */

// 1.1 exec_cmds.c
void	ft_exec_cmds(t_shell *shell, t_cmd *cmd);
void	ft_exec_solo_cmd(t_shell *shell, t_cmd *cmd);
bool	ft_is_builtin(char *cmd_name);
int		ft_pipes_init(t_shell *shell);

// builtin_1.c
int		ft_echo(t_cmd *cmd);
int		ft_cd(t_shell *shell, t_cmd *cmd);

// heredoc_handle.c
int		ft_handle_heredoc(t_shell *shell, t_cmd *cmd, t_redirs *rdrs);
void	ft_process_all_heredocs(t_shell *shell);

// path_setup.c
char	*ft_getpath(char *cmd, char **env);
char	*ft_parse_env(char *name, char **env);
void	ft_free_arr_str(char **arr);

// redirs_setup.c
void	ft_setup_redirs(t_shell *shell, t_cmd *cmd);

// cd.c
int		ft_cd(t_shell *shell, t_cmd *cmd);

// echo.c
int		ft_echo(t_cmd *cmd);


#endif
