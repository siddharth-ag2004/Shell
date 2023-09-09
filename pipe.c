#include "headers.h"

void pipe_execute(char** command,int* semicolon_indices,int idx,int input, int output,char** history_array,ListPtr list)
{
    if (input != 0)
    {
        dup2 (input, 0);
        close (input);
    }

    if (output != 1)
    {
        dup2 (output, 1);
        close (output);
    }
    int num_elements = semicolon_indices[idx + 1] - semicolon_indices[idx] - (idx!=0);
    if(num_elements==0)
    {
        perror("Invalid use of pipe.");
        return;
    }
    char** command_copy = malloc((num_elements + 1) * sizeof(char*));
    for(int i=0;i<num_elements+1;i++)
    {
        command_copy[i] = (char*)malloc(sizeof(char)*MAX_TOKEN_LENGTH);
    }

    for (int i=0; i<=num_elements;i++)
    {
        strcpy(command_copy[i],command[semicolon_indices[idx] + i + (idx!=0)]);
    }

    execute(command_copy,num_elements+1,history_array,list);
}

void my_pipe(char** command,int com_index,char** history_array,ListPtr list)
{
    if(strcmp(command[com_index-1],"|")==0)
    {
        perror("Invalid use of pipe.");
        return;
    }
    int pipefd[2];
    int no_commands = 1;
    for(int i=0;i<com_index;i++)
    {
        if(strcmp(command[i],"|")==0)
        {
            strcpy(command[i],";");
            no_commands++;
        }
    }

    int semicolon_indices[no_commands+1];
    int s_idx = 0;
    semicolon_indices[s_idx++] = 0; 
    for(int i=0;i<com_index;i++)
    {
        if(strcmp(command[i],";")==0)
        {
            semicolon_indices[s_idx++] = i;
        }
    }
    semicolon_indices[s_idx] = com_index; 
    int input = 0;
    int temp=dup(0);
    int temp2=dup(1);
    for(int i=0;i<no_commands-1;i++)
    {
        pipe (pipefd);
        pipe_execute(command,semicolon_indices,i,input,pipefd[1],history_array,list);
        close (pipefd[1]);
        input = pipefd[0];
    }

    if (input!=0)
    {
        dup2 (input,0);
    }
    dup2(temp2,1);

    int num_elements;
    num_elements = semicolon_indices[no_commands] -semicolon_indices[no_commands-1]-1;

    if(num_elements==0)
    {
        perror("Invalid use of pipe.");
        return;
    }

    char** command_copy = malloc((num_elements+1)*sizeof(char*));
    for(int i=0;i<num_elements+1;i++)
    {
        command_copy[i] = (char*)malloc(sizeof(char)*MAX_TOKEN_LENGTH);
    }

    for (int i=0; i<num_elements;i++)
    {
        strcpy(command_copy[i],command[semicolon_indices[no_commands-1] + i + 1]);
    }
    strcpy(command_copy[num_elements],";");
    
    execute(command_copy,num_elements+1,history_array,list);
    dup2(temp,0);
}
