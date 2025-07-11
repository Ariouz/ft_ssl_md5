# include "ft_ssl.h"

t_ssl_command   *get_command_by_name(char *name) {
    size_t  index = 0;

    while (index < ssl->commands_count) {
        t_ssl_command *cmd = ssl->commands[index];
        if (ft_strncmp(name, cmd->name, ft_strlen(name)) == 0) return cmd;
        index++;
    }

    return NULL;
}