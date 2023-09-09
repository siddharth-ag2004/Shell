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
        int status;
        int ret = waitpid(Sorted_processes[i]->data, &status, WNOHANG);
        if(ret==0)
        {   
            strcpy(state,"Running");
        }
        else if(ret == -1)
        {
            strcpy(state,"Error in process status");
        }
        else
        {
            strcpy(state,"Stopped");
        }
        printf("%d : %s - %s\n",Sorted_processes[i]->data,Sorted_processes[i]->name,state);
    }
}