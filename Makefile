NAME = RTv1
LIBFT_NAME = libft.a

SRC_PATH = src/
SRC_P_PATH = src/parse/
SRC_SDL_P = src/sdl_f/
SRC_R_P = src/render/
INC_PATH = inc/
LIB_PATH = libft/

SRC =   main.c \
        main_utils.c \

SRC_PARSE = scene_parser.c \
            parse_utils_1.c \
            parse_utils_2.c \
            parse_utils_3.c \
            parse_utils_4.c \
            parse_utils_5.c \

SRC_SDL =   sdl_init.c \
            sdl_utils.c \

SRC_RENDER = render.c \
             closest_stuff.c \
             closest_stuff_util.c \
             rotate_stuff.c \
             vector_stuff.c \
             put_info_util.c \
             put_object_info.c \

OBJ_DIR = obj

SDL_CFLAGS = $(shell sdl2-config --cflags)

OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_SRC_P = $(addprefix $(OBJ_DIR)/, $(SRC_PARSE:.c=.o))

OBJ_SRC_SDL_P = $(addprefix $(OBJ_DIR)/, $(SRC_SDL:.c=.o))

OBJ_SRC_R_P = $(addprefix $(OBJ_DIR)/, $(SRC_RENDER:.c=.o))

CC	= gcc
FLG = -Werror -Wextra -Wall

CGFLAGS		=	-lmlx -framework OpenGL -framework AppKit
INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-F./frameworks
FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer
ECHO = echo

all: $(NAME)

$(NAME): $(OBJ_SRC) $(OBJ_SRC_P) $(OBJ_SRC_SDL_P) $(OBJ_SRC_R_P) $(OBJ_SDL)
	@make -C $(LIB_PATH)
	@$(CC) -O3 $(FLG) $(CGFLAGS) $(FRAMEWORKS) -g $(LIB_PATH)$(LIBFT_NAME) $(OBJ_SRC) $(OBJ_SRC_P) \
	$(OBJ_SRC_SDL_P) $(OBJ_SRC_R_P) $(OBJ_SDL) -o $(NAME)

$(OBJ_DIR)/%.o : ./src/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/parse/%.c
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/sdl_f/%.c
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/render/%.c
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/sdl/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include $(INCLUDES) -c -o $@ $<

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -C $(LIB_PATH) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIB_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
