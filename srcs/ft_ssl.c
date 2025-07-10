# include "ft_ssl.h"

t_ssl   *ssl = NULL;

void init_ssl() {
    ssl = (t_ssl *) malloc(sizeof(t_ssl));
    if (!ssl) fatal_error("Failed to allocate t_ssl");

    initialize_commands();
}

int main()
{
    init_ssl();

    clean_exit();
    return (0);
}