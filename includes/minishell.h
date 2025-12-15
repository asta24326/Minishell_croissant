/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:29:52 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/13 21:58:49 by aidarsharaf      ###   ########.fr       */
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

// for max limits macroses
# include <limits.h>


/* STRUCTURES */

/* redirections struct */
typedef struct	s_redirs
{
	int		in_fd;
	int		out_fd;
	char	*hdoc_delim;
	bool	exp_hdoc; // no - if heredoc delimeter has '  ', yes - if none
	int		hdoc_fd[2]; // on exec step
}	t_redirs;

/* command data structure */
typedef struct	s_cmd
{
//	char			*name - no need anymore
	char			**args;	//changed name
	int				args_count; //needed for parsing
	int				redirs_count; //needed for parsing
	// char			*infile;
	// char			*outfile;
	// bool			closed; // false if further input is needed through interaction
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
	pid_t	shell_pid;
}	t_shell;

/* FUNCTIONS */

/* execution folder */

// env_init.c - initialisation copy of env
char		**ft_env_dup(char **env);

// 1.1 exec_cmds.c
void		ft_exec_cmds(t_shell *shell, t_cmd *cmd);
void		ft_exec_solo_cmd(t_shell *shell, t_cmd *cmd);
bool		ft_is_builtin(char *cmd_name);
int			ft_pipes_init(t_shell *shell);

// builtin_1.c
int			ft_echo(t_cmd *cmd);
int			ft_cd(t_shell *shell, t_cmd *cmd);

// heredoc_handle.c
int			ft_handle_heredoc(t_shell *shell, t_cmd *cmd, t_redirs *rdrs);
void		ft_process_all_heredocs(t_shell *shell);

// path_setup.c
char		*ft_getpath(char *cmd, char **env);
char		*ft_parse_env(char *name, char **env);
void		ft_free_arr_str(char **arr);

// redirs_setup.c
void		ft_setup_redirs(t_shell *shell, t_cmd *cmd);

// cd.c
int			ft_cd(t_shell *shell, t_cmd *cmd);

// echo.c
int			ft_echo(t_cmd *cmd);

// expand_vars.c
int			ft_expand_all_args(t_shell *shell);
char		*ft_expand_arg(t_shell *shell, char *arg);
char		*ft_expand_env_var(t_shell *shell, char *arg);
size_t		ft_get_var_name_len(char *arg);

// export.c
int			ft_export(t_shell *shell, t_cmd *cmd);
bool		ft_is_valid_var_name(char *var);

// export_utils.c
char		**ft_sort_env(char **env);
char		*ft_normalize_env_var(char *var);
void		ft_print_var_with_quotes(char *var);

// exit.c
int			ft_exit(t_shell *shell, t_cmd *cmd);

// env.c
int			ft_env(t_shell *shell, t_cmd *cmd);


/* parsing folder */

// minishell_initialization.c
int			init_minishell(t_shell *minishell);
void		handle_signal(int signum);
const char	*get_prompt(void);

// signal_handling.c
void		setup_signals(void (*signal_handler)(int));
void		handle_signal_parent(int signum);
void		handle_signal_child(int signum);

// parse_pipeline.c
int			parse_pipeline(char *pipeline, char **env);
int			get_pipe_count(char *copy);
char		*blackout_quoted_content(char *str);

// syntax_check.c
int			is_valid_syntax(char *copy);
int			are_valid_pipes(char *copy);
int			are_valid_redirs(char *copy);
int			are_closed_quotes(char *copy);

// syntax_utils.c
int			is_whitespace(char c);
int			is_operator(char c);
int			is_redir(char c);
int			is_quote(char c);
int			is_other(char c);

// create_cmd_lst.c
void		create_cmd_list(char *pipeline, int cmd_count, t_shell *minishell);
void		add_node(t_cmd **list, t_cmd *new);
t_cmd		*create_node(char *cmd_line);

// create_args_arr.c
void		create_args_arr(char *cmd_str, t_cmd *cmd);
void		fill_args_arr(char *arg_str, t_cmd *cmd);
int			get_arg_count(char *copy);
int			get_redir_count(char *copy);

// tokenize.c
void		tokenize(char *cmd_str, t_cmd *cmd);

// parse_quote.c
int			parse_quote(char *str, t_cmd *cmd);
int			get_quot_len(char *str, char quot_mark, int *env_arg);

//parse_cmd.c
int			parse_cmd(char *str, t_cmd *cmd);
int			get_arg_len(char *str);

#endif
