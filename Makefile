SOURCES		:=	main.c mlx.c player.c raycasting.c map.c parse.c utils.c movement.c dda.c draw.c textures.c draw_utils.c error.c init.c flood_fill.c utils2.c
VPATH		:=	src/
BUILD		:=	build
OBJECTS		:=	$(addprefix $(BUILD)/, $(SOURCES:.c=.o))
NAME		:=	cub3d
FLAGS		:=	-Iinclude -ldl -lglfw -pthread -lm
CC			:=	cc
LIBFT		:=	libs/libft/libft.a
LIBFT_DIR	:=	libs/libft
MLX			:=	libs/mlx/build/libmlx42.a
MLX_DIR		:=	libs/mlx
MLX_BUILD	:=	libs/mlx/build

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(MLX)
	@printf "Compiling $(NAME)\n"
	@$(CC) $(FLAGS) -o $@ $^

$(BUILD)/%.o: %.c | $(BUILD) 
	@printf "Compiling $<\n"
	@$(CC) -g $(FLAGS) -c $< -o $@

$(BUILD):
	@mkdir -p $(BUILD)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	(cd $(MLX_DIR) && cmake -B build)
	cmake --build $(MLX_BUILD) -j4

clean:
	@rm -rf $(OBJECTS) $(BUILD)
	$(MAKE) -C $(LIBFT_DIR) clean
	@printf "Cleaned ✅\n"

fclean:
	@rm -rf $(OBJECTS) $(NAME) $(BUILD) test
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX_BUILD)
	@printf "Fcleaned ✅\n"

re: fclean all

.PHONY: all test clean fclean re