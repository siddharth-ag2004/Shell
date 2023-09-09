#include "headers.h"

int containsPipe(char** command,int com_index)
{
    for(int i=0;i<com_index;i++)
    {
        if(strcmp(command[i],"|")==0)
            return 1;
    }
    return 0;
}

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
        // while((index < token_count) && (strcmp(tokens[index],";")!=0) && (strcmp(tokens[index],"&")!=0) && (strcmp(tokens[index],"|")!=0))
        while((index < token_count) && (strcmp(tokens[index],";")!=0) && (strcmp(tokens[index],"&")!=0))
        {
            strcpy(command[com_index++],tokens[index++]);
        }
        index++;
        command[com_index] = NULL;
        if(com_index==0)
        {
            perror("syntax error");
            return;
        }
        int pipe_flag = 0;
        if(containsPipe(command,com_index))
        {
            pipe_flag=1;
        }
        else if(com_index>=3)
        {
            if(strcmp(command[com_index-2],">") == 0)
            {
                redirect(command,com_index,1,history_array,list);
                return ;
            }
            if(strcmp(command[com_index-2],">>") == 0)
            {
                redirect(command,com_index,2,history_array,list);
                return ;
            }
            if(strcmp(command[com_index-2],"<") == 0)    
            {
                redirect(command,com_index,3,history_array,list);
                return ;
            }
        }
        if(pipe_flag == 1)
        {
            my_pipe(command,com_index,history_array,list);
        }
        else if((strcmp(command[0],"warp")!=0) && (strcmp(command[0],"pastevents")!=0) && (strcmp(command[0],"proclore")!=0) 
        && (strcmp(command[0],"peek")!=0) && (strcmp(command[0],"seek")!=0) && (index<=token_count) && (strcmp(tokens[index-1],";")==0))
        {
            int child = fork();
            if(child==0)
            {
                execvp(command[0],command);
                perror("Invalid command");
                return;
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
                perror("Invalid command");
                return;
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
                if(is_peek_flag(command[1]))
                    peek(command[1],NULL,NULL);
                else
                    peek(NULL,NULL,command[1]);
            }
            else if(command[3]==NULL)
            {
                if(is_peek_flag(command[1]) && is_peek_flag(command[2]))
                    peek(command[1],command[2],NULL);
                else if(is_peek_flag(command[1]) && !is_peek_flag(command[2]))
                    peek(command[1],NULL,command[2]);
            }
            else if(command[4]==NULL)
            {
                if(is_peek_flag(command[1]) && is_peek_flag(command[2]))
                    peek(command[1],command[2],command[3]);
            }
            else
            {
                perror("Invalid flags!");
            }
        }
        else if(strcmp(command[0],"seek")==0)
        { 
            if(!is_seek_flag(command[1]))
            {
                seek(NULL,NULL,command[1],command[2]);
            }
            else if(!is_seek_flag(command[2]))
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
            else if(is_seek_flag(command[1]) && is_seek_flag(command[2]))
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
            perror("Invalid command");
        }
    }
}