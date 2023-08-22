#include "headers.h"

char home_dir[PATH_MAX];
char cwd[PATH_MAX];
char last_dir[PATH_MAX];


int main()
{
    getcwd(cwd, sizeof(cwd));
    snprintf(home_dir, sizeof(home_dir), "%s", cwd);    
    ListPtr list = createList(-1,"");
    char** history_array = (char**)malloc(sizeof(char*)*15);
    for(int i=0;i<15;i++)
    {
        history_array[i] = (char*)malloc(sizeof(char)*MAX_TOKEN_LENGTH);
    }

    int history_index = 0;
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
        
        input[strlen(input)-1] = '\0';

        parse(input,history_array,history_index,list);
    }

    return 0;
}
