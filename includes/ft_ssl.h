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

# define SRC_STDIN 1
# define SRC_FILE 2
# define SRC_SFLAG 3

# define BUFF_SIZE 1024

# define ERROR_FATAL -1

# ifndef BONUS
    # define MAX_COMMANDS 2
# else
    # define MAX_COMMANDS 3
# endif

typedef struct s_flags {
    int p;
    int q;
    int r;
}   t_flags;

typedef struct s_input {
    int type;
    char *value;
    char *filename;
}   t_input;

typedef struct s_ssl_command {
    char    *name;
    char    *description;
    int     (*execute)();
}   t_ssl_command;


typedef struct s_ssl {
    size_t          commands_count;
    t_ssl_command   **commands;
    t_list          *inputs;
    t_flags         *flags;
    int             has_s;
    int             has_f;
}   t_ssl;


extern t_ssl *ssl;

int     parse_commands(int argc, char **argv);

int     init_flags();
int     init_input_lst();
int     parse_inputs(int argc, char **argv, int start_index);

void    print_stdin_digest(void *state, t_input *input, void (*digest_function)(void *));
void    print_sflag_digest(void *state, t_input *input, void (*digest_function)(void *), char *prefix);
void    print_file_digest(void *state, t_input *input, void (*digest_function)(void *), char *prefix);

t_ssl_command   *get_command_by_name(char *name);

int    fatal_error(char *msg);
int    file_error(char *msg);
int    fatal_print_help(char *msg);
int    initialize_commands();

int     read_file_to(char *src_file, char **dst);

void    clean_exit();

#endif