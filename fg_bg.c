#include "headers.h"

void child_handler(int pid)
{
    setpgid(pid, 0);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);   
    tcsetpgrp(STDIN_FILENO, pid);
}

void parent_handler()
{
    tcsetpgrp(STDIN_FILENO, getpgid(0));    
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}

void bg(char* pid_str)
{
    int pid = atoi(pid_str);
    if(pid==0)
    {
        perror("Valid pid not found");
    }
    int ret = kill(pid,SIGCONT);
    if(ret!=0)
    {
        perror("No such process found");
    }
}

void fg(char* pid_str)
{
    int pid = atoi(pid_str);
    if(pid==0)
    {
        perror("Valid pid not found");
    }
    int r = kill(pid,SIGCONT);
    if(r!=0)
    {
        perror("No such process found");
    }
    child_handler(pid);
    int status;
    int ret = waitpid(pid,&status,WUNTRACED);
    parent_handler();
}