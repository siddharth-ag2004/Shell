#include "headers.h"

void execute(char** tokens,int token_count,char** history_array,ListPtr list)
{
    int index = 0;
    while(index<token_count)
    {
        char** command = (char**)malloc(sizeof(char*)*(token_count+1));
        for (int i = 0; i <= token_count; i++) 
        {
            command[i] = (char*)malloc(sizeof(char)*MAX_TOKEN_LENGTH);
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
        if((strcmp(command[0],"warp")!=0) && (strcmp(command[0],"pastevents")!=0) && (strcmp(command[0],"proclore")!=0) 
        && (strcmp(command[0],"peek")!=0) && (strcmp(command[0],"seek")!=0) && (index<=token_count) && (strcmp(tokens[index-1],";")==0))
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
        else if((strcmp(command[0],"warp")!=0) && (strcmp(command[0],"pastevents")!=0)  && (strcmp(command[0],"proclore")!=0)
        && (strcmp(command[0],"peek")!=0) && (strcmp(command[0],"seek")!=0) && (index<=token_count) && (strcmp(tokens[index-1],"&")==0))
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
                printf("[%d]\n",child);
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
            pastevents(history_array,command[1],command[2],list);
        }
        else if(strcmp(command[0],"proclore")==0)
        {
            proclore(command[1]);
        }
        else if(strcmp(command[0],"peek")==0)
        {
            if(command[1]==NULL)
            {
                peek(NULL,NULL,NULL);
            }
            else if(command[2]==NULL)
            {
                if(isflag(command[1]))
                    peek(command[1],NULL,NULL);
                else
                    peek(NULL,NULL,command[1]);
            }
            else if(command[3]==NULL)
            {
                if(isflag(command[1]) && isflag(command[2]))
                    peek(command[1],command[2],NULL);
                else if(isflag(command[1]) && !isflag(command[2]))
                    peek(command[1],NULL,command[2]);
            }
            else if(command[4]==NULL)
            {
                peek(command[1],command[2],command[3]);
            }
            else
            {
                perror("Invalid flags!\n");
            }
        }
        else if(strcmp(command[0],"seek")==0)
        { 
            if(!isflag(command[1]))
            {
                seek(NULL,NULL,command[1],command[2]);
            }
            else if(!isflag(command[2]))
            {
                if(command[1][1]=='d')
                {
                    seek(command[1],NULL,command[2],command[3]);
                }
                else if(command[1][1]=='f')
                {
                    seek(command[1],NULL,command[2],command[3]);
                }
                else if(command[1][1]=='e')
                {
                    seek(command[1],NULL,command[2],command[3]);
                }
            }
            else if(isflag(command[1]) && isflag(command[2]))
            {
                if((command[1][1]=='d' && command[2][1]=='f') || (command[1][1]=='f' && command[2][1]=='d'))
                {
                    perror("Invalid flags!");
                }
                else
                {
                    if((command[1][1]=='d' || command[1][1]=='f'))
                    {
                        seek(command[1],command[2],command[3],command[4]);
                    }
                    else
                    {
                        seek(command[2],command[1],command[3],command[4]);
                    }
                }
            }
            
        }
        else
        {
            printf("Invalid command\n");
        }
    }
}