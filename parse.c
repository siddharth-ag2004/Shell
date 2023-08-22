#include "headers.h"

void insertSpaces(char *str)    //inserts spaces before and after ; and &
{
    int len = strlen(str);
    char newStr[2*len];
    int j = 0;

    for (int i=0; i<len;i++) 
    {
        newStr[j++] = str[i];
        if ((str[i] == ';' || str[i] == '&') && i+1<len && str[i+1] != ' ') {
            newStr[j++] = ' ';
        }
    }
    newStr[j] = '\0';
    strcpy(str, newStr); // Copy the modified string back to the original string
}

// int insertSemicolonIfNeeded(char** token) {
//     int len = strlen(token);
//     if (len>0 && (strcmp(token[len-1],";")!=0 && strcmp(token[len-1],"&")!=0)) 
//     {
//         printf("yes\n");
//         strcat(token, ";");
//         return 1;
//     }
//     return 0;
// }

int isSubstring(char* s1, char* s2) 
{
    int M = strlen(s1);
    int N = strlen(s2);
    for (int i = 0; i <= N - M; i++) 
    {
        int j;
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;
        if (j == M)
            return 1;
    }
    return 0;
}

void pastevents(char** history_array,const char* flag,const char* process)
{
    if(flag == NULL)
    {
        for(int i=0;i<15;i++)
        {
            // printf("entered\n");
            if(strcmp(history_array[(history_index+i)%15],"\0")!=0)
            {
                printf("%s\n",history_array[(history_index+i)%15]);
            }
        }
        // return NULL;
    }
    else if(strcmp(flag,"purge")==0)
    {
        for(int i=0;i<15;i++)
        {
            strcpy(history_array[i],"\0");
        }
        // return NULL;
    }
    // else
    // {
    //     int converted_process = atoi(process);
    //     return history_array[(history_index+converted_process)%15];
    // }
}

void parse(char* input,char** history_array,ListPtr list)
{
    if(!isSubstring("pastevents",input) && strcmp(input,history_array[(history_index+14)%15]))
        {
            // printf("input: %s",input);
            strcpy(history_array[history_index%15],input);             //history
            history_index = (history_index+1)%15;
        }
        
        insertSpaces(input);

        char *delimiters = " \t\v\f\r";
        char *tokens[MAX_TOKENS];
        int token_count = 0;
        
        char *token = strtok(input, delimiters);
        while (token != NULL && token_count < MAX_TOKENS) 
        {
            tokens[token_count++] = token;
            token = strtok(NULL, delimiters);
        }
        
        // if (token_count > 0) 
        // {
        //     if(insertSemicolonIfNeeded(tokens))          //if ending is not semicolon
        //     {
        //         // printf("%s",)
        //     }
        // }

        // for(int i=0;i<token_count;i++)
        // {
        //     printf("%s\n",tokens[i]);
        // }
        
        int index = 0;
        // printf("%d\n",token_count);
        while(index<token_count)
        {
            char** command = (char**)malloc(sizeof(char*)*(token_count + 1));
            for (int i = 0; i <= token_count; i++) 
            {
                command[i] = (char*)malloc(sizeof(char) * MAX_TOKEN_LENGTH);
            }
            // printf("%d:  ",index);
            int com_index = 0;
            while((index < token_count) && (strcmp(tokens[index],";")!=0) && (strcmp(tokens[index],"&")!=0))
            {
                strcpy(command[com_index++],tokens[index++]);
            }
            index++;
            command[com_index] = NULL;

            // printf("%s %s\n",command[0],command[1]);
            // printf("%d %d\n",index,token_count);
            if((strcmp(command[0],"warp")!=0) && (strcmp(command[0],"pastevents")!=0) && (index<=token_count) && (strcmp(tokens[index-1],";")==0))
            {
                int child = fork();
                if(child==0)
                {
                    execvp(command[0],command);
                }
                else if(child == -1)
                {
                    perror("fork");
                }
                else
                {
                    int status;
                    waitpid(child, &status, 0);
                }
                // execvp(command[0],command);
            }
            else if((strcmp(command[0],"warp")!=0) && (strcmp(command[0],"pastevents")!=0) && (index<=token_count) && (strcmp(tokens[index-1],"&")==0))
            {
                int child = fork();
                if(child==0)
                {
                    execvp(command[0],command);
                    // printf("Sleep exited normally (%d)\n",getpid());
                }
                else if(child == -1)
                {
                    perror("fork");
                }
                else
                {
                    addNode(list,child,command[0]);
                    // continue;
                }
                // execvp(command[0],command);
            }
            else if(strcmp(command[0],"warp")==0)
            {
                if(com_index==1)
                {
                    warp("~\0");
                }
                for(int i=1;i<com_index;i++)
                {
                    warp(command[i]);
                }
            }
            else if(strcmp(command[0],"pastevents")==0)
            {
                // for(int i=1;i<com_index;i++)
                // {
                //     warp(command[i]);
                // }
                // printf("%d\n",history_index);   
                pastevents(history_array,command[1],command[2]);
            }
        }
}