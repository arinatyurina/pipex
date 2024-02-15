# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atyurina <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 16:51:30 by atyurina          #+#    #+#              #
#    Updated: 2024/02/13 15:48:42 by atyurina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Это переменная, содержащая имя исполняемого файла
NAME := pipex

# Это переменная, содержащая список  исходных файлов
SRC := pipex.c ft_split.c ft_strjoin.c \
	pipes_managing.c check_path.c \
	
BSRC := pipex.c ft_split.c ft_strjoin.c \
	pipes_managing.c check_path_bonus.c \
# Это переменная, содержащая список ваших объектных файлов (.o), 
# полученных из исходных файлов.
# OBJ := $(SRC:.c=.o) 
# BOBJ := $(BSRC:.c=.o)
# Это переменная, содержащая компилятор, 
# который будет использоваться для компиляции вашего кода.
# -g включает информацию для отладчика.
CC = gcc
CFLAGS = -Wall -Wextra -Werror
# Эти переменные используются для определения пути к объектным файлам.
OBJ_PATH	= obj/
OBJ		= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

BOBJ_PATH	= bobj/
BOBJ		= $(BSRC:.c=.o)
BOBJS		= $(addprefix $(BOBJ_PATH), $(BOBJ))
# Цель all компилирует исполняемый файл.
all: $(NAME)

# Это правило компиляции .c файлов в объектные файлы (.o).
# mkdir -p $(dir $@) создаст директорию, 
# если ее нет, перед компиляцией объектного файла
$(OBJ_PATH)%.o: %.c
	@mkdir -p $(dir $@) 
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(BOBJ_PATH)%.o: %.c
	@mkdir -p $(dir $@) 
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
# Это зависимость для объектных файлов от пути к объектам. 
# Обеспечивает создание директории, если ее нет.
$(OBJS): $(OBJ_PATH)

$(BOBJS): $(BOBJ_PATH)
# Это правило создания директории для объектных файлов.
$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
	
$(BOBJ_PATH):
	@mkdir $(BOBJ_PATH)
# Это правило, которое компилирует исполняемый файл.
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Цель clean удаляет все объектные файлы и вызывает make clean в mlx.
clean:
	@rm -rf $(OBJ_PATH) $(BOBJ_PATH)

# Цель fclean удаляет все объектные файлы и исполняемый файл.
fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: $(BOBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(BOBJS)

.PHONY: all re clean fclean
