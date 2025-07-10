#ifndef FT_SSL
# define FT_SSL

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../lib/libft/libft.h"

# include "md5.h"

# define true 0
# define false 1

# ifndef BONUS
    # define MAX_COMMANDS 2
# else
    # define MAX_COMMANDS 3
# endif

typedef struct s_ssl_command {
    char    *name;
    char    *description;
    int     (*execute)(char *args);
}   t_ssl_command;


typedef struct s_ssl {
    size_t          commands_count;
    t_ssl_command   **commands;
}   t_ssl;


extern t_ssl *ssl;

void    fatal_error(char *msg);
void    initialize_commands();

void    clean_exit();

#endif