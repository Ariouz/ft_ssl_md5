# include "ft_ssl.h"

int parse_commands(int argc, char **argv) {
    if (argc < 2) return fatal_print_help("A command is required");

    t_ssl_command *command = get_command_by_name(argv[1]);
    if (!command) return fatal_print_help("Unknown command");

    if (init_input_lst() == ERROR_FATAL) return ERROR_FATAL;
    if (init_flags() == ERROR_FATAL) return ERROR_FATAL;
    
    if (parse_inputs(argc, argv, 2) == ERROR_FATAL) return ERROR_FATAL;

    command->execute();
    return 0;
}

