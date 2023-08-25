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
    else
    {
        int converted_process = atoi(process);          //error handling if  >15
        if (converted_process <= 15)
        {
            // Calculate the index of the line to modify
            int target_index = (history_index - converted_process + 15) % 15;

            // Read history.txt
            FILE* history_file = fopen("history.txt", "r+");
            if (history_file == NULL)
            {
                perror("Error opening history file");
                return;
            }

            // // Find the line to modify
            char line[1000]; // Adjust size accordingly
            for (int i = 0; i <= history_index; i++)
            {
                if (fgets(line, sizeof(line), history_file) == NULL)
                {
                    perror("Error reading history file");
                    fclose(history_file);
                    return;
                }
            }

            char pattern[100];
            snprintf(pattern, sizeof(pattern), "pastevents execute %s", process);

            char* pattern_occurrence = strstr(line, pattern);

            if (pattern_occurrence)
            {
                strcpy(pattern_occurrence, line);
            }

            // Rewind the file and write the modified content
            fseek(history_file, -strlen(line), SEEK_CUR);
            fprintf(history_file, "%s", line);
            fclose(history_file);

            // Your parsing logic here
            parse(history_array[(history_index-converted_process+15)%15], history_array, list);
        }
    }
}