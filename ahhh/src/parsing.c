#include "pipex.h"

char *check_path(char *path, char **env)
{
    int i = 0;

    while(env[i])
    {
       if(ft_strncmp(path, env[i], 5) == 0)
           return(env[i] + 5);
       i++;
    }
    return(NULL);
}

char *get_direct_path(char *cmd, char **env)
{
    char *path;
    char *full_path;

    if (cmd[0] == '~')
    {
        path = check_path("HOME=", env);
        if (!path)
            return (NULL);
        full_path = ft_strjoin(path, cmd + 1);
        if (access(full_path, X_OK) == -1)
        {
            free(full_path);
            ft_perror(DOESNT_EXECUTABLE, EXIT_EXV);
        }
        return (full_path);
    }
    else
    {
        if (access(cmd, X_OK) == -1)
            ft_perror(DOESNT_EXECUTABLE, EXIT_EXV);
        return (cmd);
    }
}

char *get_path_from_env(char *cmd, char **env)
{
    char *path;
    char *full_path;
    char **dir;
    int i = 0;

    path = check_path("PATH=", env);
    if (!path)
        return (NULL);
    dir = ft_split(path, ':');
    if (!dir)
        return (NULL);
    while (dir[i])
    {
        full_path = ft_strjoin_three(dir[i], "/", cmd);
        if(!full_path)
      {
        ft_free_last_result(dir, LENGHT_PATH);
        return(NULL);  
      }
        if (access(full_path, X_OK) != -1)
            return (full_path);
        free(full_path);
        i++;
    }
      ft_free_last_result(dir, LENGHT_PATH);
      return(NULL);  
}

char *get_path(char *cmd, char **env)
{
    if (!cmd)
        return (NULL);
    if (ft_strchr(cmd, '/'))
        return (get_direct_path(cmd, env));
    else
        return (get_path_from_env(cmd, env));
}

t_list *tokenize_cmd(char **args, int argc, int is_heredoc)
{
    t_list (*new_node), (*head);
    head = NULL;
    while (argc > 1 + is_heredoc)
      {
        new_node = malloc(sizeof(t_list));
        if (!new_node && !head)
        {
            ft_free_all_commands(head);
            ft_perror(ALL_FAILED, EXIT_FAILURE);
        }
        new_node->cmd = args[argc];
        new_node->argv = ft_split(args[argc], ' ');
        new_node->next = head;
        head = new_node;
        argc--;
    }
    return head;
}
