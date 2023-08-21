#include "headers.h"

char home_dir[PATH_MAX];
char cwd[PATH_MAX];
char last_dir[PATH_MAX];

typedef struct List* ListPtr;

typedef struct List
{
    int data;
    char* name;
    struct List* next;
}List;

ListPtr createList(int data,char* name)
{
    ListPtr list = (ListPtr)malloc(sizeof(List));
    list->data = data;
    list->name = (char*)malloc(sizeof(char)*MAX_TOKEN_LENGTH);
    strcpy(list->name,name);
    list->next = NULL;
    return list;
}

void addNode(ListPtr list, int data,char* name)
{
    ListPtr node = createList(data,name);
    ListPtr temp = list;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}

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

int main()
{
    getcwd(cwd, sizeof(cwd));
    snprintf(home_dir, sizeof(home_dir), "%s", cwd);    
    ListPtr list = createList(-1,"");
    // strcpy(cwd,"osn");
    while (1)
    {
        // strcpy(last_dir,cwd);
        prompt();
        ListPtr temp = list;
        temp=temp->next;
        while(temp!=NULL)
        {
            int status;
            int ret = waitpid(temp->data, &status, WNOHANG);
            if(ret==0)
            {
                temp = temp->next;
            }
            else if(ret==-1)
            {
                // perror("waitpid");
                temp = temp->next;
            }
            else
            {
                // printf("Process %d exited normally\n",temp->data);
                printf("%s with pid %d exited normally\n",temp->name,temp->data);
                temp = temp->next;
            }
        }
        char input[4096];
        fgets(input, 4096, stdin);

        input[strlen(input) - 1] = '\0';
        
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
            else if((strcmp(command[0],"warp")!=0) && (index<=token_count) && (strcmp(tokens[index-1],"&")==0))
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
                for(int i=1;i<com_index;i++)
                {
                    warp(command[i]);
                }
            }
        }

    }

    return 0;
}
