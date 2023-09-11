#include "headers.h"

char home_dir[PATH_MAX];
char cwd[PATH_MAX];
char last_dir[PATH_MAX];
char commandline_input[MAX_TOKEN_LENGTH];
int history_index;
int time_count=0;
int pt;
char *input = NULL;
int curr_fg;


void INThandler(int sig)
{
    // signal(sig, SIG_IGN);    
    pt = 0;
    input[0] = '\0';
    if(curr_fg==0)
    {
        printf("\n");
        prompt();
    }
}


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
    if (file == NULL) 
    {
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
    input = malloc(sizeof(char)*100);
    struct sigaction action;
    // memset(&action, 0, sizeof(action));
    action.sa_handler = INThandler;
    action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &action, NULL);
    signal(SIGTSTP,SIG_IGN);
    while (1)
    {
        // strcpy(last_dir,cwd);
        // signal(SIGINT, INThandler);
        // if(curr_fg == 0)
        prompt();

        // enableRawMode();
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
                removeNode(list,temp->data);
                temp = temp->next;
            }
            else
            {
                // printf("Process %d exited normally\n",temp->data);
                if(WIFEXITED(status))
                {
                    printf("%s exited normally (%d)\n",temp->name,temp->data);
                }
                else
                {
                    printf("%s exited abnormally (%d)\n",temp->name,temp->data);
                }
                removeNode(list,temp->data);
                temp = temp->next;
            }
        }
        // char input[4096];
        // fgets(input, 4096, stdin);
        input_in_rawmode();

        strcpy(commandline_input,input);
        time_t initial_time;
        time(&initial_time);
        parse(input,history_array,list);
        time_t final_time;
        time(&final_time);
        if(final_time-initial_time<=2)
        {
            strcpy(commandline_input,"");
            time_count=0;
        }
        else
        {
            time_count = (int)(final_time-initial_time);
        }
    }

    return 0;
}
