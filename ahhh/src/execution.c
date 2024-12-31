#include "pipex.h"

static void handle_last_command(t_list *command, s_name *name) 
{
    int fd;
    if (name->name_output) 
    {
        fd = open(name->name_output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            ft_perror(FAILER_FD, EXIT_FAILURE);
        command->output = fd;
    }
}

static void handle_first_command(t_list *command, s_name *name) 
{
    int fd;
    if (name->name_input) 
    {
        fd = open(name->name_input, O_RDONLY);
        if (fd == -1)
            ft_perror(FAILER_FD, EXIT_FAILURE);
        command->input = fd;
    }
}

void execute(t_list *command, s_name *name) 
{
    char *full_path = get_path(command->argv[0], name->env);
    if (!full_path)
    {
        ft_free_all_commands(commands);
        ft_perror(COMMAND_FAILED, EXIT_FAILURE);
    }
    
    if (execve(full_path, command->argv, name->env) == -1)
    {
        free(full_path);
        ft_perror(FAILED_EX, EXIT_COMMAND);
    }
    free(full_path);
}

void hna_khdma_process(t_list *command, s_name *name, int *fd) 
{
    if (dup2(command->input, STDIN_FILENO) == -1) 
    {
        close(fd[1]); 
        ft_perror(DUP2_FAILED, EXIT_FAILURE);
    }
    if (dup2(command->output, STDOUT_FILENO) == -1) 
    {
        close(fd[1]);
        ft_perror(DUP2_FAILED, EXIT_FAILURE);
    }
    close(command->output);
    close(command->input);
    close(name->pipe_fd[0]);
    
    execute(command, name);
}

static void handle_pipe(t_list *command, s_name *name) 
{
    if (pipe(name->pipe_fd) == -1)
        ft_perror(PIPE_FAILED, EXIT_FAILURE);
    command->output = name->pipe_fd[1];
}

void waiting_parents(int *pid, int count_command)
{
    int i = 0;
    while(i < count_command)
        waitpid(pid[i++], NULL, 0);
}

static void process_command(t_list *command, s_name *name) 
{
    pid_t pid[1024];
    int command_index = 0;
    
    while (command) 
    {
        if (command_index == 0)
            handle_first_command(command, name);
        if (command->next == NULL)
            handle_last_command(command, name);
        if (command->next != NULL)
            handle_pipe(command, name);
        pid[command_index] = fork();
        if (pid[command_index] == -1)
            ft_perror(FORK_FAILER, EXIT_FAILURE);
        if(pid[command_index] == 0)
            hna_khdma_process(command, name, name->pipe_fd);
        close(command->input);
        close(command->output);
        command = command->next; 
        if (command)
            command->input = name->pipe_fd[0];
        command_index++;
    }
    waiting_parents(pid, command_index);
}

void execute_pipeline(t_list *command, s_name *name) 
{
    if (!command || !name || !name->env)
        ft_perror("Invalid arguments", EXIT_FAILURE);
    
    process_command(command, name);
}
