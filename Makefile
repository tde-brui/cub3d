SOURCES		:=	main.c
VPATH		:=	src/
BUILD		:=	build
OBJECTS		:=	$(addprefix $(BUILD)/, $(SOURCES:.c=.o))
NAME		:=	cub3d
FLAGS		:=	-Wall -Werror -Wextra
CC			:=	cc
LIBFT		:=	libft/libft.a
LIB_DIR		:=	libft

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	@printf "Compiling $(NAME)\n"
	@$(CC) $(FLAGS) -o $@ $< 

$(BUILD)/%.o: %.c | $(BUILD) 
	@printf "Compiling $<\n"
	@$(CC) -g $(FLAGS) -c $< -o $@

$(BUILD):
	@mkdir -p $(BUILD)

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	@rm -rf $(OBJECTS) $(BUILD)
	$(MAKE) -C $(LIB_DIR) clean
	@printf "Cleaned ✅\n"

fclean:
	@rm -rf $(OBJECTS) $(NAME) $(BUILD) test
	$(MAKE) -C $(LIB_DIR) fclean
	@printf "Fcleaned ✅\n"

re: fclean all

.PHONY: all test clean fclean re