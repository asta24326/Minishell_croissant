NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -I includes
RL_FLAGS = -lreadline -lhistory

LIBFT_DIR = libraries/libft
LIBFT_A = $(LIBFT_DIR)/libft.a

SRC_DIR = src
PRS_DIR = $(SRC_DIR)/parsing
EXEC_DIR = $(SRC_DIR)/execution
INCL_DIR = includes

SRC =	$(PRS_DIR)/0.1.main.c \
		$(PRS_DIR)/0.2.minishell_initialization.c \
		$(PRS_DIR)/0.3.signal_handling.c \
		$(PRS_DIR)/0.4.minishell_termination.c \
		$(PRS_DIR)/1.1.parsing.c \
		$(PRS_DIR)/1.2.syntax_check.c \
		$(PRS_DIR)/1.3.syntax_utils.c \
		$(PRS_DIR)/1.4.prepare_parsing.c \
		$(PRS_DIR)/2.1.parse_cmd_line.c \
		$(PRS_DIR)/2.2.prepare_cmd_lst.c \
		$(PRS_DIR)/2.3.prepare_args_arr.c \
		$(PRS_DIR)/2.4.prepare_redirs.c \
		$(PRS_DIR)/3.1.tokenize.c \
		$(PRS_DIR)/3.2.parse_cmd.c \
		$(PRS_DIR)/3.3.parse_redir.c \
		$(PRS_DIR)/4.1.handle_quotes.c \
		$(PRS_DIR)/4.2.check_builtin_cmds.c \
		$(PRS_DIR)/4.3.handle_redirs.c \
		$(PRS_DIR)/_print_parsing_results.c \
		$(EXEC_DIR)/env_init.c \

OBJ = $(SRC:.c=.o)

INCLUDES = -I $(INCL_DIT) -I $(LIBF_DIR)

all: $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT_A) $(RL_FLAGS)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline_suppress.supp ./$(NAME)

valchild: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=readline_suppress.supp ./$(NAME)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
