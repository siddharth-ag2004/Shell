#ifndef __PIPE_H
#define __PIPE_H

void my_pipe(char** command,int com_index,char** history_array,ListPtr list);
void pipe_execute(char** command,int* semicolon_indices,int idx,int input, int output,char** history_array,ListPtr list);

#endif