#include "headers.h"

void pastevents(char** history_array,const char* flag,const char* process,ListPtr list)
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
    else if(strcmp(flag,"execute")==0)
    {
        int converted_process = atoi(process);          //error handling if  >15
        if (converted_process <= 15)
        {
            char string_copy[PATH_MAX];
            strcpy(string_copy,history_array[(history_index-converted_process+15)%15]);
            parse(string_copy, history_array, list);
        }
    }
}