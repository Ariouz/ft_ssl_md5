#ifndef FT_SSL
# define FT_SSL

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../lib/libft/libft.h"

# include "md5.h"
# include "sha256.h"

# define true 0
# define false 1

# define ERROR_FATAL -1

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

int    parse_commands(int argc, char **argv);

t_ssl_command   *get_command_by_name(char *name);

int    fatal_error(char *msg);
int    fatal_print_help(char *msg);
int    initialize_commands();

void    clean_exit();

#endif