#include "pipex.h"

char *check_path(char *path, char **env)
{
    int i = 0;

    while (env[i])
    {
        if (ft_strncmp(path, env[i], 5) == 0)
            return (env[i] + 5);
        i++;
    }
    return (NULL);
}

char *get_path(char *cmd, char **env)
{
    char *path, *full_path;
    char **dir;
    int i = 0;

    if (ft_strchr(cmd, '/'))
    {
        if (cmd[0] == '~')
        {
            path = check_path("HOME=", env);
            full_path = ft_strjoin(path, cmd + 1);
            if (!full_path || access(full_path, X_OK) == -1)
            {
                free(full_path);
                return NULL;
            }
            return full_path;
        }
        else
        {
            if (access(cmd, X_OK) == -1)
                return NULL;
            return cmd;
        }
    }
    else if (cmd[0])
    {
        path = check_path("PATH=", env);
        if (!path)
            return (NULL);
        dir = ft_split(path, ':');
        if (!dir)
            return NULL;
        while (dir[i])
        {
            full_path = ft_strjoin_three(dir[i], "/", cmd);
            if (!full_path)
            {
                ft_free_split(dir);
                return NULL;
            }
            if (access(full_path, X_OK) != -1)
            {
                ft_free_split(dir);
                return full_path;
            }
            free(full_path);
            i++;
        }
        ft_free_split(dir);
    }
    return (NULL);
}

void take_io_file_name(int index, s_name *name, char *args)
{
    if (index == 1)
        name->name_input = args;
    else
        name->name_output = args;
}

t_list *tokenize_cmd(char **args, int argc, s_name *name)
{
    t_list *new_node, *head;
    int last_idx = argc - 1;

    head = NULL;
    while (--argc >= 1)
    {
        if (argc == 1 || argc == last_idx)
        {
            take_io_file_name(argc, name, args[argc]);
            continue;
      }
        new_node = malloc(sizeof(t_list));
        if (!new_node)
        {
            ft_free_node(head);
            ft_perror(ALL_FAILED, EXIT_FAILURE);
        }
        new_node->cmd = ft_strdup(args[argc]);
        if (!new_node->cmd)
        {
            free(new_node);
            ft_free_node(head);
            ft_perror(ALL_FAILED, EXIT_FAILURE);
        }
        new_node->argv = ft_split(args[argc], ' ');
        if (!new_node->argv)
        {
            free(new_node->cmd);
            free(new_node);
            ft_free_node(head);
            ft_perror(ALL_FAILED, EXIT_FAILURE);
        }
        new_node->next = head;
        head = new_node;
    }
    return head;
}

