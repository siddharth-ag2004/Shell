#include "headers.h"

char home_dir[PATH_MAX];
char cwd[PATH_MAX];
char last_dir[PATH_MAX];

int main()
{
    getcwd(cwd, sizeof(cwd));
    snprintf(home_dir, sizeof(home_dir), "%s", cwd);    
    // strcpy(cwd,"osn");
    while (1)
    {
        // strcpy(last_dir,cwd);
        prompt();
        char input[4096];
        fgets(input, 4096, stdin);

        input[strlen(input) - 1] = '\0';
    
        char *delimiters = " \t\v\f\r";
        char *tokens[MAX_TOKENS];
        int token_count = 0;
        
        char *token = strtok(input, delimiters);
        while (token != NULL && token_count < MAX_TOKENS) 
        {
            tokens[token_count++] = token;
            token = strtok(NULL, delimiters);
        }


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
            if((strcmp(command[0],"warp")!=0) && (index<=token_count) && (strcmp(tokens[index-1],";")==0))
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
            else if((strcmp(command[0],"warp")!=0) && (index<token_count) && (strcmp(tokens[index-1],"&")==0))
            {
                int child = fork();
                if(child==0)
                {
                    printf("%d\n",child);
                    execvp(command[0],command);
                }
                else if(child == -1)
                {
                    perror("fork");
                }
                else
                {
                    printf("%d\n",child);
                    // continue;
                }
                // execvp(command[0],command);
            }
            else if(strcmp(command[0],"warp")==0)
            {
                for(int i=1;i<com_index;i++)
                {
                    warp(command[i]);
                }
            }
        }

    }

    return 0;
}
