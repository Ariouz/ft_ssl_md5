# include "ft_ssl.h"

void free_commands() {
    size_t  index = 0;

    while (index < ssl->commands_count) {
        free(ssl->commands[index]);
        index++;
    }
    free(ssl->commands);
}

void free_exit() {
    free_commands();
    free(ssl);
}

void clean_exit() {
    free_exit();
}

void fatal_error(char *msg) {
    ft_printf("ERROR: %s\n", msg);
    clean_exit();
}
