#ifndef FT_SSL
# define FT_SSL

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define true 0
# define false 1

typedef struct ssl_command {
    char    *name;
    char    *description;
    int     *execute;
}   t_ssl_command;


#endif