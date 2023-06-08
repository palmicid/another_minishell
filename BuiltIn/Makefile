CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -rf
NAME = test_prog

BLTIN_UTILS = utils_1.c
BLTIN_ERRMSG = bltin_errmsg.c
TEST_FILE = pwd.c env.c cd.c unset.c

SRCS = testinitenv.c $(TEST_FILE) $(BLTIN_UTILS) $(BLTIN_ERRMSG)
OBJS = $(SRCS:.c=.o)

LIBFT = ../libft/libft.a

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf *.o

fclean: clean
	@$(RM) $(NAME)

re: fclean all

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
