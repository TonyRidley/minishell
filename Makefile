# Executable Name
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Idependencies/libft/includes
LDFLAGS = -lreadline

# Libft
LIB_DIR = dependencies/libft
LIBFT = $(LIB_DIR)/libft.a

# Source and Object files
SRC_PATH = src/
SRC =	src/main.c \
		src/signal_handling.c \
		src/signal_handling_2.c \
		src/lexing/tokenize_input.c \
		src/lexing/lexing.c \
		src/lexing/lexing_small_helpers.c \
		src/lexing/lexing_big_helpers.c \
		src/lexing/valid_syntax.c \
		src/parsing/parsing.c \
		src/parsing/token_to_cmd.c \
		src/parsing/handle_tokens.c \
		src/parsing/handle_tokens_helpers.c \
		src/parsing/set_redirect_field.c \
		src/parsing/parse_helpers.c \
		src/parsing/expand/vars_from_cmd.c \
		src/parsing/expand/env_vars.c \
		src/parsing/expand/env_vars_helpers.c \
		src/parsing/expand/handle_vars.c \
		src/execution/execution.c \
		src/execution/execution_utils.c \
		src/execution/external_command/external_command.c \
		src/execution/external_command/external_command_helpers.c \
		src/execution/pipe.c \
		src/execution/builtin/cd.c \
		src/execution/builtin/echo.c \
		src/execution/builtin/env.c \
		src/execution/builtin/exit.c \
		src/execution/builtin/export.c \
		src/execution/builtin/export_helpers.c \
		src/execution/builtin/pwd.c \
		src/execution/builtin/unset.c \
		src/execution/redirections/setup_redirections.c \
		src/execution/redirections/setup_heredoc.c \
		src/execution/redirections/setup_heredoc_helpers.c \
		src/execution/redirections/read_line_simple.c \
		src/execution/redirections/execute_pipeline.c

OBJ_PATH = obj/
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

# Build the executables
all: $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -sC $(LIB_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)

clean:
	rm -rf $(OBJ_PATH)
	cd $(LIB_DIR) && make clean

fclean: clean
	rm -f $(NAME)
	cd $(LIB_DIR) && make fclean

re: fclean all

.PHONY: all clean fclean re