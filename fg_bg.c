#include "headers.h"

void make_fg_process(pid_t pid)
{
    // Give the process its own process group
    setpgid(pid, 0);
    // Ignore SIGTTIN & SIGTTOU so shell doesn't get suspended
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);   
    // Set the process gpid to foreground gpid
    tcsetpgrp(STDIN_FILENO, pid);
}

void make_fg_parent(){
    // Set parent back to foreground process gid
    tcsetpgrp(STDIN_FILENO, getpgid(0));    
    // Set TTIN & TTOUT handlers back to default
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}

void bg(char* pid_str)
{
    int pid = atoi(pid_str);
    kill(pid,SIGCONT);
}

void fg(char* pid_str)
{
    int pid = atoi(pid_str);
    kill(pid,SIGCONT);
    make_fg_process(pid);
    int status;
    int ret = waitpid(pid,&status,WUNTRACED);
    make_fg_parent();
}