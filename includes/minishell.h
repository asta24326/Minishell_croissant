/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:29:52 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/22 22:24:40 by aidarsharaf      ###   ########.fr       */
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
	char	**list; //needed for parsing
	int		in_fd;
	int		out_fd;
	int		hdoc_count; //added
	char	*hdoc_delim;
	bool	exp_hdoc; // no - if heredoc delimeter has '  ', yes - if none
	int		hdoc_fd[2]; // on exec step
}	t_redirs;

/* command data structure */
typedef struct	s_cmd
{
	int				index; //needed for redirs handling (parsing)
	char			**args;	//changed name
	int				args_count; //needed for parsing
	int				redirs_count; //needed for parsing
	bool			builtin;// true if is builtin command
	t_redirs		*redirs;
	struct s_cmd	*next;
}	t_cmd;

/* main data storage */
typedef struct	s_shell
{
	char	*prompt;
	int		pipe_count;
	int		**pipes;
	char	**env;
	t_cmd	*cmd;
	int		exit_status;
	pid_t	shell_pid;
}	t_shell;

/* FUNCTIONS */

/* PARSING FOLDER */

// minishell_initialization.c
int			init_minishell(t_shell *minishell);

// signal_handling.c
void		setup_signals(void (*signal_handler)(int));
void		handle_signal_parent(int signum);
void		handle_signal_child(int signum);

// minishell_termination.c
void		end_minishell(t_shell *minishell);

// parsing.c
int			parse(char *pipeline, t_shell *minishell);
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

// prepare_parsing.c
void		prepare_parsing(char *copy, t_shell *minishell);
int			get_pipe_count(char *copy);

// parse_cmd_line.c
int			parse_cmd_lines(char *pipeline, int cmd_count, t_shell *minishell);

// prepare_cmd_lst.c
void		create_cmd_list(char **arr, int cmd_count, t_shell *minishell);
void		add_node(t_cmd **list, t_cmd *new);
t_cmd		*create_node(char *cmd_line);
void		set_index(t_cmd *stack, int cmd_count);

// prepare_args_arr.c
int			prepare_args_arr(char *copy, t_cmd *cmd);
int			get_arg_count(char *copy, int redirs_count);
int			get_redir_count(char *copy);

//prepare_redirs.c
int			prepare_redirs(char *copy, t_cmd *cmd);
int			get_hdoc_count(char *copy);

// tokenize.c
int			tokenize(char *cmd_str, t_cmd *cmd);

//parse_cmd.c
int			parse_cmd(char *str, t_cmd *cmd);
int			get_arg_len(char *str);
void		fill_args_arr(char *arg_str, t_cmd *cmd);

//parse_redir.c
int			parse_redir(char *cmd_str, t_cmd *cmd);
int			prepare_hdoc(char *cmd_str, t_redirs *redirs, int len);
char		*get_delimiter(char *cmd_str, int len);
int			get_redir_len(char *str);
void		fill_redirs_arr(char *redirect, t_cmd *cmd);

//handle_quotes.c
int			cleanup_quotes(char **arr);
char		*get_clean_str(char *orig_str);
int			get_strlen_clean(char *orig_str);

//check_builtin_cmds.c
int			is_builtin_cmd(t_cmd *cmd);

//handle_redirs.c
int			handle_redirs(t_cmd *cmd);
char		*get_filename(char *redir_str);
int			handle_infile(char *filename, t_cmd *cmd);
int			handle_out_redir(char *filename, t_cmd *cmd, int op_count);

//_print_parsing_results.c - only for testing, will go out
void		print_list(t_cmd *cmd, int cmd_count);

/* ==================== */

/* EXECUTION FOLDER */

// 5.1.exec_cmds.c
void		ft_exec_cmds(t_shell *shell);
void		ft_exec_solo_cmd(t_shell *shell, t_cmd *cmd);

// 5.2.exec_builtin.c
int			ft_exec_builtin(t_shell *shell, t_cmd *cmd, char *cmd_name);

// 5.3.exec_sys_cmd.c
int			ft_exec_sys_cmd(t_shell *shell, t_cmd *cmd);

// 5.4.path_setup.c
char		*ft_getpath(char *cmd, char **env);
char		*ft_parse_env(char *name, char **env);
void		ft_free_arr_str(char **arr);

// 5.5.redirs_setup.c
void		ft_setup_redirs(t_shell *shell, t_cmd *cmd);

// 6.1.cd.c
int			ft_cd(t_shell *shell, t_cmd *cmd);

// 6.2.echo.c
int			ft_echo(t_cmd *cmd);

// 6.3.env.c
int			ft_env(t_shell *shell, t_cmd *cmd);

// 6.4.exit.c
int			ft_exit(t_shell *shell, t_cmd *cmd);

// 6.5.1.export.c
int			ft_export(t_shell *shell, t_cmd *cmd);
bool		ft_is_valid_var_name(char *var);

// 6.5.2.export_utils.c
char		**ft_sort_env(char **env);
char		*ft_normalize_env_var(char *var);
void		ft_print_var_with_quotes(char *var);

// 6.6.pwd.c
int			ft_pwd(t_shell *shell, t_cmd *cmd);

// 6.7.unset.c
int			ft_unset(t_shell *shell, t_cmd *cmd);

// 7.1.expand.c
int			ft_expand(t_shell *shell);
char		*ft_expand_arg(t_shell *shell, char *arg);
int			ft_expand_hdoc_delims(t_shell *shell);

// 7.2.expand_utils.c
size_t		ft_get_var_name_len(char *arg);
char		*ft_expand_env_var(t_shell *shell, char *arg);

// 8.1.env_init.c
char		**ft_env_dup(char **env);

// 9.1.heredoc_handle.c
void		ft_process_all_heredocs(t_shell *shell);
int			ft_handle_heredoc(t_shell *shell, t_cmd *cmd);

// 10.1.cleanup_and_exit.c
void		ft_cleanup_and_exit(t_shell *shell, int exit_code);
void		ft_cleanup_shell(t_shell *shell);
void		ft_cleanup_cmd_list(t_cmd **cmd_list);
void		ft_cleanup_cmd(t_cmd *cmd);
void		ft_cleanup_redirs(t_redirs *redirs);

// 11.1.pipes_handle.c
int			ft_pipes_init(t_shell *shell);
void		ft_setup_pipes_for_cmd(t_shell *shell, int cmd_index);
void		ft_close_all_pipes(t_shell *shell);
void		ft_close_unused_pipes(t_shell *shell, t_cmd *cmd, int cmd_index);
void		ft_cleanup_pipes_array(t_shell *shell);

#endif
