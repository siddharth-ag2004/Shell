#include "headers.h"

void redirect(char** command,int com_index,int direction,char** history_array,ListPtr list)
{
    int fd;
    if(direction==1)
    {
        fd = open(command[com_index-1], O_WRONLY|O_TRUNC|O_CREAT, 0644);
    }
    if(direction == 2)
    {
        fd = open(command[com_index-1], O_WRONLY|O_CREAT|O_APPEND, 0644);
    }
    if(direction!=3)
    {
        if (fd < 0) 
        { 
            perror("Error opening file.");
            return;
        }
            
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("Error in forking");
            return;
        }

        if (child_pid == 0) 
        {
            if (dup2(fd, 1) < 0) 
            {
                perror("Error: Unable to redirect output to file descriptor");
                return;
            }

            close(fd);
            strcpy(command[com_index-2],";");
            execute(command,com_index-1,history_array,list);

            exit(0);
        } 
        else 
        {
            close(fd);
            if (dup2(STDOUT_FILENO, 1) < 0) 
            {
                perror("dup2");
                return;
            }
        }
    }
    else
    {
        fd= open(command[com_index-1], O_RDONLY);
        if (fd < 0) 
        { 
            perror("Error opening file.");
            return;
        }

        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            return;
        }

        if (child_pid == 0) 
        {
            if (dup2(fd, 0) < 0) 
            {
                perror("Error: Unable to redirect input to file descriptor");
                return;
            }

            close(fd);
            strcpy(command[com_index-2], ";");
            execute(command, com_index - 1, history_array, list);

            exit(0);
        } 
        else 
        {
            close(fd);
            wait(NULL); // Wait for the child process to finish
        }

    }
}