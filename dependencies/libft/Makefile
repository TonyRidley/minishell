# Project Name
NAME = libft.a

# Compiler
CC = cc

# Compiler Flags
CFLAGS = -Wall -Wextra -Werror -Iincludes

# Directories for Source and Object Files
SRC_DIR = src
OBJ_DIR = obj
LIB2_DIR = $(SRC_DIR)/corelib2/
LIBFT_DIR = $(SRC_DIR)/corelib/
PRINTF_DIR = $(SRC_DIR)/printf/

# Automatically Detect All Source Files in Directories
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)*.c)
LIB2_SRCS = $(wildcard $(LIB2_DIR)*.c)
FT_PRINTF_SRCS = $(wildcard $(PRINTF_DIR)*.c) $(wildcard $(PRINTF_DIR)specifiers/*.c)

# Combine All Source Files
SRCS = $(LIBFT_SRCS) $(FT_PRINTF_SRCS) $(LIB2_SRCS)

# Object Files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

# Create the library
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Compile source files into object files inside the OBJ_DIR
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Rules
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

# Rebuild Everything
re: fclean all

.PHONY: all clean fclean re