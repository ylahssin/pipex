#include "pipex.h"

void ft_perror(char *msg , int num)
{
    write(2, msg, ft_strlen(msg));
    exit(num);
}
