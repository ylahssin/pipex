#include "pipex.h"

static char *read_here_doc(char *limit, int ac) 
{
  if(ac < 6)
      return NULL;
    char *random_str = "nicmok";
    int fd = open(random_str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char *line;
    if (fd < 0)
        return NULL;
    while ((line = get_next_line(STDIN_FILENO))) 
    {
        if (ft_strncmp(limit, line, ft_strlen(limit)) == 0 && line[ft_strlen(limit)] == '\n') 
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        free(line);
    }
    return(close(fd), random_str);
}

int main(int ac, char **av, char **env)
{
    t_list *tokenized_list;
    s_name *name = malloc(sizeof(s_name));
    name->env = env;
    name->ac = ac;
    if (ac < 5 || !name)
    {
        free(name);
        ft_perror(ERROR_MS_AR, EXIT_FAILURE);
    }
    if(!ft_strncmp(av[1], HERDOC, ft_strlen(HERDOC)))
    {
        name->name_input = read_here_doc(av[2], name->ac);
        if(!name->name_input)
        { 
            free(name);
        //change this cheat : nikmok;
            ft_perror("no valid argement", 127);
        }
        tokenized_list = tokenize_cmd(av, name->ac - 2, 1);
    }
    else 
    {
        name->name_input = av[1];
        tokenized_list = tokenize_cmd(av, name->ac - 2, 0);
    }
    name->name_output = av[ac-1];
    execute_pipeline(tokenized_list, name);
    ft_free_all_commands(tokenized_list);
    free(name);
    return SUCCESS;
}
