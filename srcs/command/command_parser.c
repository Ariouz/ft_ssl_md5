# include "ft_ssl.h"

int parse_commands(int argc, char **argv) {
    if (argc < 2) return fatal_print_help("A command is required");

    t_ssl_command *command = get_command_by_name(argv[1]);
    if (!command) return fatal_print_help("Unknown command");

    if (argc < 3) return fatal_error("Please provide a string to hash");

    char *str_to_hash = argv[2];
    // todo check argc > 3 =>>>> flags

    command->execute(str_to_hash);
    return 0;
}

