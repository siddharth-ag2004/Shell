#include "headers.h"

char home_dir[PATH_MAX];
char cwd[PATH_MAX];
char last_dir[PATH_MAX];
int history_index;
int bg_process_count=0;

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

    history_index = 0;


    FILE* file = fopen("history.txt", "r");
    if (file == NULL) {
        perror("Failed to open the file");
        return 1;
    }

    char buffer[MAX_TOKEN_LENGTH];
    while (history_index < 15 && fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') 
        {
            buffer[length - 1] = '\0';
        }

        strcpy(history_array[history_index], buffer);

        history_index++;
    }
    fclose(file);
    history_index = 0;
    
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
                temp = temp->next;
            }
            else
            {
                // printf("Process %d exited normally\n",temp->data);
                printf("%s exited normally (%d)\n",temp->name,temp->data);
                removeNode(list,temp->data);
                temp = temp->next;
            }
        }
        char input[4096];
        fgets(input, 4096, stdin);
        
        input[strlen(input)-1] = '\0';

        parse(input,history_array,list);
    }

    return 0;
}
