#include "ft_ssl.h"

void    print_stdin_digest(void* state, t_input *input, void (*digest_function)(void *)) {
    // doesn't print stdin if -p is not set and atleast 1 of file/-s is set
    if (ssl->flags->p == 0 && (ssl->has_f == true || ssl->has_s == true)) return ;

    if (ssl->flags->q == 1) {
        if (ssl->flags->p == 1) ft_printf("%s\n", input->value);
    } else {
        if (ssl->flags->p == 1) ft_printf("(\"%s\")= ",  input->value);
        else ft_printf("(stdin)= ");
    }

    digest_function(state);
    ft_printf("\n");
}

void print_sflag_digest(void* state, t_input *input, void (*digest_function)(void *), char *prefix) {
    if (ssl->flags->q == 1) {
        digest_function(state);
        ft_printf("\n");
        return;
    }
    if (ssl->flags->r == 1) {
        digest_function(state);
        ft_printf(" \"%s\"\n", input->value);
        return;
    }

    ft_printf("%s (\"%s\") = ", prefix, input->value);
    digest_function(state);
    ft_printf("\n");
}


void    print_file_digest(void* state, t_input *input, void (*digest_function)(void *), char *prefix) {
    if (ssl->flags->q == 1) {
        digest_function(state);
        ft_printf("\n");
        return;
    }
    if (ssl->flags->r == 1) {
        digest_function(state);
        ft_printf(" %s\n", input->filename);
        return;
    }

    ft_printf("%s (%s) = ", prefix, input->filename);
    digest_function(state);
    ft_printf("\n");
}