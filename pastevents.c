#include "headers.h"

char* pastevents(char** history_array,int history_index,const char* flag,const char* process)
{
    if(flag == NULL)
    {
        for(int i=1;i<=15;i++)
        {
            if(strcpy(history_array[(history_index-i+15)%15],"\0")!=0)
            {
                printf("%s\n",history_array[i]);
            }
        }
    }
}
