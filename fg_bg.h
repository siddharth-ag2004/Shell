#ifndef __FG_BG_H
#define __FG_BG_H

void bg(char* pid_str);
void fg(char* pid_str);
void child_handler(int pid);
void parent_handler();

#endif