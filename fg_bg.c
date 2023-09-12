#include "headers.h"

void make_fg_process(pid_t pid)
{
    setpgid(pid, 0);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);   
    tcsetpgrp(STDIN_FILENO, pid);
}

void make_fg_parent(){
    tcsetpgrp(STDIN_FILENO, getpgid(0));    
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}

void bg(char* pid_str)
{
    int pid = atoi(pid_str);
    int ret = kill(pid,SIGCONT);
    if(ret!=0)
    {
        perror("No such process found");
    }
}

void fg(char* pid_str)
{
    int pid = atoi(pid_str);
    int r = kill(pid,SIGCONT);
    if(r!=0)
    {
        perror("No such process found");
    }
    make_fg_process(pid);
    int status;
    int ret = waitpid(pid,&status,WUNTRACED);
    make_fg_parent();
}