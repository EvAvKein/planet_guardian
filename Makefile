NAME := planet_guardian

SRC_DIR := src
SRC_FILES := main.c \
             textures.c \
             gameplay_frame.c \
             movement.c \
			 initialize_asteroids.c \
			 collision_detection.c \
			 draw_sprites.c \
			 draw_shield.c \
			 planet_condition.c \
			 text.c \
			 sounds.c \
			 state.c
INCLUDE_DIR := incl

LIB_FILES := raylib5_6.a
LIB_INCLUDE_DIR := raylib/src

COMPILE_FLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIB_INCLUDE_DIR)
LIBRARY_FLAGS := -lm -ldl -lpthread -lGL -lrt -lX11
DEBUG_FLAGS := -g

SRC_OBJ := $(SRC_FILES:%.c=$(SRC_DIR)/%.o)

all: $(NAME)

%.o: %.c
	cc $(COMPILE_FLAGS) -c $< -o $@

$(NAME): $(LIB_FILES) $(SRC_OBJ)
	clang $(SRC_OBJ) $(LIB_FILES) $(COMPILE_FLAGS) $(LIBRARY_FLAGS) -o $(NAME)

clean:
	@rm -f $(SRC_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

neat: $(NAME) clean
	clear

debug: COMPILE_FLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re neat debug
