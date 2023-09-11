#include "headers.h"

int cmpfunc(const void* a, const void* b) 
{
    ListPtr listA = *(ListPtr*)a;
    ListPtr listB = *(ListPtr*)b;

    if (listA->data < listB->data) 
        return -1;
    else if (listA->data > listB->data)
        return 1;
    else 
        return 0; 
}

void activities(ListPtr list)
{
    int list_len = 0;
    ListPtr temp = list;
    temp=temp->next;

    while(temp!= NULL)
    {
        list_len++;
        temp=temp->next;
    }

    ListPtr Sorted_processes[list_len];
    temp = list;
    temp=temp->next;
    int proc_count=0;
    while(temp!= NULL)
    {
        // int status;
        // int ret = waitpid(temp->data, &status, WNOHANG);
        Sorted_processes[proc_count++] = temp;
        temp=temp->next;
    }
    // printf("%d\n",list_len);
    qsort(Sorted_processes,list_len,sizeof(ListPtr),cmpfunc);

    for(int i=0;i<list_len;i++)
    {
        char* state = (char*)malloc(sizeof(char)*50);
        // int status;
        // int ret = waitpid(Sorted_processes[i]->data, &status, WNOHANG);
        char proc_status_path[PATH_MAX];
        snprintf(proc_status_path, sizeof(proc_status_path), "/proc/%d/status" ,Sorted_processes[i]->data);
        FILE* status_file = fopen(proc_status_path, "r");
        char line[256];
        while (fgets(line, sizeof(line), status_file)) 
        {
            if (strncmp(line, "State:", 6) == 0) 
            {
                const char *property = line + 7; 
                const char *status_end = strchr(property, ' ');
                if (status_end == NULL)
                {
                    status_end = line + strlen(line);
                }

                int status_length = status_end - property;
                char status[status_length + 1];

                strncpy(status, property, status_length);
                status[status_length] = '\0';
                if(strcmp(status,"T")==0)
                {   
                    strcpy(state,"Stopped");
                }
                // else if(ret == -1)
                // {
                //     strcpy(state,"Error in process status");
                // }
                else
                {
                    strcpy(state,"Running");
                }
                printf("%d : %s - %s\n",Sorted_processes[i]->data,Sorted_processes[i]->name,state);
            }
        }
        fclose(status_file);
        // if(ret==0)
        // {   
        //     strcpy(state,"Running");
        // }
        // else if(ret == -1)
        // {
        //     strcpy(state,"Error in process status");
        // }
        // else
        // {
        //     strcpy(state,"Stopped");
        // }
    }
}