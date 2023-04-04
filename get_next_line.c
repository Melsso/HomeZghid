#include "get_next_line.h"

char    *ft_strchr(const char *str, int c)
{
    while(str && *str)
    {
        if (*str == (char)c)
            return ((char *)str);
        str++;
    }
    if (str && *str == (char)c)
        return ((char *)str);
    return (NULL);
}

char    *ft_get_line(char *str)
{
    int     i;
    char    *line;

    i = 0;
    if (!str[i])
        return (NULL);
    while(str[i] && str[i] != '\n')
        i++;
    line = (char *)ft_calloc(i + 2, 1);
    i = 0;
    while(str[i] && str[i] != '\n')
    {
        line[i] = str[i];
        i++;
    }
    if (str[i] && str[i] == '\n')
        line[i] = '\n';
    return (line);
}

char    *ft_get_buffer(char *str)
{
    char    *buffer;
    int     i;
    int     j;

    i = 0;
    while(str && str[i] && str[i] != '\n')
        i++;
    j = 0;
    buffer = ft_calloc(ft_strlen(str) - i + 1, 1);
    while(str && str[i])
        buffer[j++] = str[++i];
    buffer[j] = '\0';
    free(str);
    return (buffer);
}

char    *get_next_line(int fd)
{
    static char *str;
    char        *tmp;
    ssize_t     bytes_read;
    char        *buffer;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
            return (NULL);
    if (!str)
        str = ft_calloc(1, 1);
    bytes_read = 1;
    buffer = ft_calloc(BUFFER_SIZE + 1, 1);
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
            {
                free(buffer);
                free(str);
                str = NULL;
                return (NULL);
            }
        buffer[bytes_read] = 0;
        tmp = str;
        str = ft_strjoin(tmp, buffer);
        free(tmp);
        if (ft_strchr(str, '\n'))
            break ; // stop reading
    }
    free(buffer);
    line = ft_get_line(str);
    tmp = str;
    str = ft_get_buffer(tmp);
    if (bytes_read == 0 && str[0] == 0)
        {
            free(str);
            str = NULL;
        }
    return (line);
}