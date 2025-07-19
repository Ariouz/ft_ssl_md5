#include "ft_ssl.h"

int read_file_to(char *src_file, char **dst) {
    char buffer[BUFF_SIZE];
    char *result = NULL;
    ssize_t bytes_read;
    size_t total_size = 0;

    int fd = open(src_file, O_RDONLY);
    if (fd < 0) return fatal_error("Failed to open file");

    while ((bytes_read = read(fd, buffer, BUFF_SIZE)) > 0) {
        char *new_result = malloc(total_size + bytes_read + 1);
        if (!new_result) {
            free(result);
            return fatal_error("malloc failed in read_file_to");
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
        return fatal_error("no input from file");


    free(*dst);
    *dst = ft_strdup(result);
    free(result);
    return 0;
}