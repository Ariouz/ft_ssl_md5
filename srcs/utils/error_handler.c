# include "ft_ssl.h"

void free_inputs() {
    t_list *inputs = ssl->inputs;

    t_list *curr = inputs->next;
    while (curr) {
        t_input *input = (t_input*) curr->content;
        if (input->filename) free(input->filename);
        if (input->value) free(input->value);
        free(input);
    
        t_list *tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    free(inputs);
}

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
    free_inputs();
    free(ssl->flags);
    free(ssl);
}

void clean_exit() {
    free_exit();
}

int fatal_error(char *msg) {
    ft_printf("ERROR: %s\n", msg);
    clean_exit();
    return ERROR_FATAL;
}

int fatal_print_help(char *msg) {
    ft_printf("ERROR: %s\n", msg);

    ft_printf("\nCommands:\n");
    size_t  index = 0;
    while (index < ssl->commands_count) {
        t_ssl_command *command = ssl->commands[index];
        ft_printf("%s: %s\n", command->name, command->description);
        index++;
    }
    clean_exit();
    return ERROR_FATAL;
}