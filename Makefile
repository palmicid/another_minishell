# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 17:30:06 by bsirikam          #+#    #+#              #
#    Updated: 2023/06/02 15:39:41 by pruangde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME = uname -s

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -rf
NAME = minishell

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

# MAC M2
LDFLAGS = -L${HOMEBREW_PREFIX}/opt/readline/lib
CPPFLAGS = -I${HOMEBREW_PREFIX}/opt/readline/include

# School MAC
# LDFLAGS		= -L/usr/local/opt/readline/
# CPPFLAGS	= -I/usr/local/opt/readline/include/

# UBUNTU - not work finding new
# LDFLAGS		= -L/usr/include/readline/
# CPPFLAGS	= -I/usr/local/opt/readline/include/



PARS = parser_1.c parser_2.c parser_3.c parser_4.c parser_5.c parser_6.c
UTIL = utils_1.c utils_2.c utils_3.c utils_4.c utils_5.c
BLTIN = 
EXEC = 
ERRMSG = err_msg.c


SRCS = minishell.c sig_handle.c env.c $(PARS) $(UTIL) $(ERRMSG) $(BLTIN) $(EXEC)
OBJ_C = $(SRCS:.c=.o)
OBJ_DIR = obj
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJ_C))

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< ${CPPFLAGS} -o $@

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -lreadline $(LIBFT) $(OBJS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(OBJS) $(BN_OBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

re: fclean all

# test:
#	$(CC) maintest.c $(NAME)
#	valgrind --vgdb=no --leak-check=full --show-leak-kinds=all ./a.out
# san:
# 	$(CC) -fsanitize=address -fno-omit-frame-pointer maintest.c

norm:
	@echo "------------------------------------"
	@echo " !!!!!!!!   NORMINETTE   !!!!!!!!"
	@echo ""
	@norminette -R CheckForbiddenSourceHeader *.c
	@echo ""
	@echo ""
	@norminette -R CheckDefine *.h
	@echo ""
	@echo "------------------------------------"

normhead:
	@echo "------------------------------------"
	@echo " !!!!!!!!   NORMINETTE   !!!!!!!!"
	@echo " !!!!!!!   ONLY  HEADER   !!!!!!!!"
	@echo ""
	@norminette -R CheckDefine *.h
	@echo ""
	@echo "------------------------------------"
