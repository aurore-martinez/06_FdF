# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 09:29:59 by aumartin          #+#    #+#              #
#    Updated: 2025/04/04 16:12:21 by aumartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

V = false

ifeq ($(V),true)
	ECHO =
else
	ECHO = @
endif

# Compiler
NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -DGL_SILENCE_DEPRECATION
OS = $(shell uname | tr '[:upper:]' '[:lower:]')

MAKE = make -sC
MKDIR = mkdir -p
RM = rm -rf

# Libs
LIB_DIR = lib
LIB = $(LIB_DIR)/lib.a
LINKER = $(LIB)

# MiniLibX - Platform-dependent compilation
ifeq ($(OS), linux)
	MLX_DIR			?= minilibx-linux
	MLX				= $(MLX_DIR)/libmlx.a
	LINKER			+= -lmlx -lm -lz -lXext -lX11 -L $(MLX_DIR)
	INCLUDES_FLAG	+= -I$(MLX_DIR)
else
	MLX_DIR			?= minilibx_macos
	MLX				= $(MLX_DIR)/libmlx.a
	LINKER			+= -lmlx -lm -framework OpenGl -framework Appkit -L $(MLX_DIR)
	INCLUDES_FLAG	+= -I$(MLX_DIR)
endif

# Info
$(info 🖥️ OS détecté : $(OS))
$(info 📂 MiniLibX dir : $(MLX_DIR))

# Includes
INCLUDE_DIR = include
LIB_SUBDIR = $(wildcard $(LIB_DIR)/*)

INCLUDE_FLAG = -I$(INCLUDE_DIR) \
			   $(foreach dir, $(LIB_SUBDIR), -I$(dir))

INCLUDE = $(wildcard $(INCLUDE_DIR)/*.h) \
		  $(foreach dir, $(LIB_SUBDIR), $(wildcard $(dir)/*.h))

# Sources
SRC_DIR = src/
SRC_FILES = bonus.c \
			draw_line.c \
			engine.c \
			events.c \
			map.c \
			map_parsing.c \
			projection.c \
			render.c \
			utils.c

SRCS = main.c $(addprefix $(SRC_DIR), $(SRC_FILES))

# Objects
OBJS_DIR = objs/
OBJ_FILES = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

# Couleurs ANSI pour affichage
GREEN = \033[32m
RED = \033[31m
RESET = \033[0m
YELLOW = \033[33m
CLEAR_LINE = \033[2K\r   # Supprime la ligne active du terminal

# Compilation principale
all: $(LIB) $(MLX) $(OBJS_DIR) $(NAME)

$(LIB):
	@echo "$(YELLOW)📦 Compilation de la lib...$(RESET)\r"
	@$(MAKE) $(LIB_DIR) > /dev/null 2>&1 \
	&& echo -e "$(CLEAR_LINE)✅ Compilation lib réussie (✔)" \
	|| { echo -e "$(CLEAR_LINE)❌ Erreur : Compilation de la lib échouée (✘)"; exit 1; }

$(MLX):
	@echo "$(YELLOW)📦 Compilation de MiniLibX...$(RESET)\r"
	@$(MAKE) $(MLX_DIR) > /dev/null 2>&1 \
	&& echo -e "$(CLEAR_LINE)✅ Compilation mlx réussie (✔)" \
	|| { echo -e "$(CLEAR_LINE)❌ Erreur : Compilation de MiniLibX échouée (✘)"; exit 1; }

$(OBJS_DIR):
	@$(MKDIR) $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE) | $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAG) -c $< -o $@

$(OBJS_DIR)main.o: main.c $(INCLUDE) | $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAG) -c $< -o $(OBJS_DIR)main.o

$(NAME): $(OBJS) $(LIB) $(MLX)
	@echo "🚀 Compilation de $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LINKER) $(FRAMEWORKS) -o $(NAME) \
	&& echo "✅ $(NAME) a été créé avec succès (✔)" \
	|| { echo "❌ Erreur : Compilation de $(NAME) échouée (✘)"; exit 1; }

# Nettoyage
clean:
	@echo "$(YELLOW)🧹 Nettoyage clean en cours...$(RESET)\r"
	@$(RM) $(OBJS_DIR)
	@echo -e "$(CLEAR_LINE)✅ Nettoyage clean réussi (✔)"


fclean: clean
	@echo "$(YELLOW)🧼 Nettoyage complet fclean en cours...$(RESET)\r"
	@$(RM) $(NAME)
	@$(MAKE) $(MLX_DIR) clean
	@$(MAKE) $(LIB_DIR) fclean
	@echo -e "$(CLEAR_LINE)✅ Nettoyage complet fclean réussi (✔)"

re: fclean all

.PHONY: all clean fclean re
