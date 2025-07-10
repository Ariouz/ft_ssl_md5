# include "ft_ssl.h"

void    register_command(char *name, char *description, int (*execute)(char *args)) {
    t_ssl_command   *command;

    command = (t_ssl_command *) malloc(sizeof(t_ssl_command));
    if (!command) fatal_error("Failed to allocate command");

    command->name = name;
    command->description = description;
    command->execute = execute;

    if (ssl->commands_count >= MAX_COMMANDS) fatal_error("Trying to register a command but MAX_COMMANDS is reached");

    ssl->commands[ssl->commands_count] = command;
    ssl->commands_count++;

    ft_printf("Registered command %s\n", command->name);
}

void    initialize_commands() {
    ssl->commands_count = 0;
    ssl->commands = (t_ssl_command **) malloc(sizeof(t_ssl_command*) * MAX_COMMANDS);

    register_command("md5", "The md5 hashing algorithm", md5_hash);
}