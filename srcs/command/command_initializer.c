# include "ft_ssl.h"

int    register_command(char *name, char *description, int (*execute)(char *args)) {
    t_ssl_command   *command;

    command = (t_ssl_command *) malloc(sizeof(t_ssl_command));
    if (!command) return fatal_error("Failed to allocate command");

    command->name = name;
    command->description = description;
    command->execute = execute;

    if (ssl->commands_count >= MAX_COMMANDS) return fatal_error("Trying to register a command but MAX_COMMANDS is reached");

    ssl->commands[ssl->commands_count] = command;
    ssl->commands_count++;

    //ft_printf("Registered command %s\n", command->name); // DEBUG
    return 0;
}

int    initialize_commands() {
    ssl->commands_count = 0;
    ssl->commands = (t_ssl_command **) malloc(sizeof(t_ssl_command*) * MAX_COMMANDS);

    if (register_command("md5", "The md5 hashing algorithm", md5_hash) == ERROR_FATAL) return ERROR_FATAL;
    if (register_command("sha256", "The SHA256 hashing algorithm", sha256_hash) == ERROR_FATAL) return ERROR_FATAL;

    return 0;
}