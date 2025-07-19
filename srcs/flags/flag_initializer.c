#include "ft_ssl.h"

int init_input_lst() {
    t_list *inputs = ft_lstnew(NULL);

    if (!inputs) return fatal_error("Failed to allocate inputs list");
    ssl->inputs = inputs;

    return 0;
}

int init_flags() {
    t_flags *flags;

    flags = (t_flags*) malloc(sizeof(t_flags));
    if (!flags) return fatal_error("Failed to allocate flags");

    flags->p = 0;
    flags->q = 0;
    flags->r = 0;

    ssl->flags = flags;
    return 0;
}

int add_input(int type, char *value) {
    t_input *input;

    input = malloc(sizeof(t_input));
    if (!input) return fatal_error("Failed to allocate input");
    input->type = type;
    input->value = value;
    if (type == SRC_FILE) input->filename = ft_strdup(value);
    else input->filename = NULL;

    ft_lstadd_back(&ssl->inputs, ft_lstnew(input));

    ft_printf("add input with value %s and type %d\n", value, type);
    return 0;
}

int read_stdin() {
    char buffer[BUFF_SIZE];
    char *result = NULL;
    ssize_t bytes_read;
    size_t total_size = 0;

    while ((bytes_read = read(STDIN_FILENO, buffer, BUFF_SIZE)) > 0) {
        char *new_result = malloc(total_size + bytes_read + 1);
        if (!new_result) {
            free(result);
            return fatal_error("malloc failed in read_stdin");
        }
        if (result) {
            ft_memcpy(new_result, result, total_size);
            free(result);
        }
        ft_memcpy(new_result + total_size, buffer, bytes_read);
        total_size += bytes_read;
        new_result[total_size] = '\0';
        result = new_result;
    }
    if (!result)
        return 0;

    size_t len = ft_strlen(result);
    if (len > 0 && result[len - 1] == '\n')
        result[len - 1] = '\0';

    add_input(SRC_STDIN, result);
    return 0;
}

int parse_inputs(int argc, char **argv, int start_index) {
    
    read_stdin();
    
    for (int i = start_index; i < argc; i++) {
        if (ft_strncmp(argv[i], "-p", ft_strlen(argv[i])) == 0)
            ssl->flags->p = 1;

        else if (ft_strncmp(argv[i], "-q", ft_strlen(argv[i])) == 0)
            ssl->flags->q = 1;

        else if (ft_strncmp(argv[i], "-r", ft_strlen(argv[i])) == 0)
            ssl->flags->r = 1;

        else if (ft_strncmp(argv[i], "-s", ft_strlen(argv[i])) == 0) {
            i++;
            if (i == argc) return fatal_error("-s arg requires a value");
            add_input(SRC_SFLAG, ft_strdup(argv[i]));
            ssl->has_s = true;
        }

        else {
            add_input(SRC_FILE, ft_strdup(argv[i]));
            ssl->has_f = true;
        }
    }

    return 0;
}
