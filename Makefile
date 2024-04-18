NAME =		minishell

SRC =		src/minishell.c \
			src/commands/builtin.c src/commands/cd.c src/commands/echo.c src/commands/env.c src/commands/exit.c src/commands/export.c src/commands/pwd.c src/commands/unset.c \
			src/parse/check_input.c src/parse/expand_token.c src/parse/get_input.c src/parse/parse.c src/parse/trim_quotes.c\
			src/pipex/pipex.c src/pipex/pipex_utils.c \
			src/signals/signal.c \
			src/tools/env_tools.c src/tools/smart_split.c src/tools/tools.c src/tools/string_tools.c

CFLAGS =	-Wall -Wextra # -Werror #-fsanitize=address

RED =		\033[0;31m
BLUE =		\033[0;34m
GREEN =		\033[0;32m
RESET =		\033[0m

LIBFTPATH =	./libft/
LIBFT =		$(LIBFTPATH)libft.a

OBJ_DIR =	obj

OBJ =		$(SRC:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	cc $(CFLAGS) -c $< -o $@

$(NAME) :	$(OBJ_DIR) $(OBJ)
	@echo "$(BLUE)Building $(NAME)...$(RESET)"
	make -C $(LIBFTPATH) all -s
	cc $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)$(NAME) built$(RESET)"

all :		$(NAME)

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	make -C $(LIBFTPATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTPATH) fclean

re: fclean all

.PHONY:
	all clean fclean re