#ifndef __EXECUTE_H
#define __EXECUTE_H

void execute(char** tokens,int token_count,char** history_array,ListPtr list);
void child_handler(int pid);
void parent_handler();
void parse(char* input,char** history_array,ListPtr list);
void pastevents(char** history_array,const char* flag,const char* process,ListPtr list);
void my_pipe(char** command,int com_index,char** history_array,ListPtr list);
void redirect(char** command,int com_index,int direction,char** history_array,ListPtr list);
void proclore(char* flag);
void peek(char* flag1,char* flag2,char* path);
void seek(char* flag1, char* flag2,char* target,char* path);
int is_peek_flag(char* token);
int is_seek_flag(char* token);
void activities(ListPtr list);
void ping(char* pid_str,char* signal_number_str);
void bg(char* pid_str);
void fg(char* pid_str);
void neonate(char* time_str);
int isSubstring(char* s1, char* s2);


#endif