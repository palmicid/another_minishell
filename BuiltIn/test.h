#include "../libft/libft.h"
#include <limits.h>
#include <sys/signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/stat.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char	**environ;

// void	mini_cd(void);
// void	mini_echo(void);
// void	mini_env(void);
// void	mini_exit(void);
// void	mini_export(void);
void	mini_pwd(void);
// void	mini_unset(void);
