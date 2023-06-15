# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 17:03:50 by kkaiyawo          #+#    #+#              #
#    Updated: 2023/06/15 15:19:06 by kkaiyawo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
NAME			=	minishell

### DIR ###
SRC_DIR			=	./src/
BONUS_DIR		=	./bonus/
LIB_DIR			=	./lib/
BUILD_DIR		=	./build/
READLINE_DIR	=	/usr/local/opt/readline/
# READLINE_DIR	=	${HOMEBREW_PREFIX}/opt/readline/

### FILES ###
SRC_FILE		=	minishell.c env.c sig_handle.c debugger.c\
					parser_1.c parser_2.c parser_3.c parser_4.c parser_5.c \
					parser_6.c \
					utils_1.c utils_2.c utils_3.c utils_4.c utils_5.c \
					err_msg.c \
					arr_utils.c file_utils.c parser.c fs_utils.c ps_utils.c\
					exec_utils.c pseudopipex.c executor.c pseudopipex_cmd.c\
					executor_utils.c malloc_utils.c\
					bltin_cd.c bltin_echo.c bltin_env.c bltin_errmsg.c\
					bltin_exit.c bltin_export.c bltin_pwd.c bltin_unset.c\
					bltin_utils_1.c
BONUS_FILE		=	${SRC_FILE}
LIB_FILE		=	libft/libft.a

### PATH ###
SRC				=	${addprefix ${BUILD_DIR},${SRC_FILE}}
BONUS			=	${addprefix ${BUILD_DIR},${BONUS_FILE}}
LIB				=	${addprefix ${LIB_DIR},${LIB_FILE}}

### OBJECTS ###
SRC_OBJ			=	${SRC:.c=.o}
BONUS_OBJ		=	${BONUS:.c=.o}

### COMPILATION ###
CC				=	gcc
CFLAG			=	-g -Wall -Wextra -Werror #-fsanitize=address
RM				=	rm -rf
RLINCL			=	-I$(READLINE_DIR)include/
RLLIB			=	-lreadline -L$(READLINE_DIR)lib/

all:			${LIB} ${BUILD_DIR} ${NAME}

${NAME}:		${SRC_OBJ}
					${CC} ${CFLAG} ${RLLIB} ${SRC_OBJ} ${wildcard ${LIB_DIR}*/*.a} -o ${NAME}

bonus:			${LIB} ${BUILD_DIR} ${BONUS_OBJ}
					${CC} ${CFLAG} -o ${NAME} ${BONUS_OBJ} ${LIB}

${LIB}:
					find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make -C {} \;

${BUILD_DIR}:
					mkdir -p ${BUILD_DIR}

${BUILD_DIR}%.o:${SRC_DIR}%.c
					${CC} ${CFLAG} ${RLINCL} ${CPPFLAGS} -c -o $@ $^

${BUILD_DIR}%.o:${BONUS_DIR}%.c
					${CC} ${CFLAG} ${RLINCL} ${CPPFLAGS} -c -o $@ $^

clean:
					${RM} ${SRC_OBJ} ${BONUS_OBJ}
					find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make clean -C {} \;

fclean:			clean
					${RM} ${NAME}
					find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make fclean -C {} \;

re:				fclean all

b:				bonus clean

m:				all clean

.PHONY:			all clean fclean re bonus
