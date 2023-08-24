#ifndef __PARSE_H
#define __PARSE_H

void parse(char* input,char** history_array,ListPtr list);
void pastevents(char** history_array,const char* flag,const char* process,ListPtr list);
void proclore(char* flag);
void peek(char* flag1,char* flag2,char* path);
void seek(char* flag1, char* flag2,char* target,char* path);
int isflag(char* token);
int isSubstring(char* s1, char* s2); 

#endif