# include "ft_ssl.h"

t_ssl   *ssl = NULL;

int init_ssl() {
    ssl = (t_ssl *) malloc(sizeof(t_ssl));
    if (!ssl) return fatal_error("Failed to allocate t_ssl");

    return initialize_commands();
}

int main(int argc, char **argv)
{
    if (init_ssl() == ERROR_FATAL) return 1;
    if (parse_commands(argc, argv) == ERROR_FATAL) return 1;

    clean_exit();
    return (0);
}