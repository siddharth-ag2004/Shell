#include "headers.h"

void insertSpaces(char *str)    //inserts spaces before and after ; and &
{
    int len = strlen(str);
    char newStr[3*len];  // Increased size to accommodate additional spaces
    int j = 0;

    for (int i = 0; i < len; i++) 
    {
        if ((str[i] == ';' || str[i] == '&') && i - 1 >= 0 && str[i - 1] != ' ') {
            newStr[j++] = ' ';
        }
        
        newStr[j++] = str[i];

        if ((str[i] == ';' || str[i] == '&') && i + 1 < len && str[i + 1] != ' ') {
            newStr[j++] = ' ';
        }
    }
    newStr[j] = '\0';
    strcpy(str, newStr);
}

void add_semicolon_at_end(char *input) 
{
    int len = strlen(input);


    for (int i = len - 1; i >= 0; i--) 
    {
        if (input[i] != ' ' && input[i] != '\t' && input[i] != '\0' && input[i] != '\n') 
        {
            if (input[i] != ';' && input[i] != '&') 
            {
                strcat(input, " ;");
            }
            break;
        }
    }
}


int isSubstring(char* s1, char* s2) 
{
    int M = strlen(s1);
    int N = strlen(s2);
    for (int i = 0; i <= N - M; i++) 
    {
        int j;
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;
        if (j == M)
            return 1;
    }
    return 0;
}

void parse(char* input,char** history_array,ListPtr list)
{
    if(!isSubstring("pastevents",input) && strcmp(input,history_array[(history_index+14)%15]))
    {
        strcpy(history_array[history_index%15],input);             //history
        history_index = (history_index+1)%15;
        FILE* file = fopen("history.txt", "w");
        for (int i = history_index;i<history_index+15;i++) 
        {
            fprintf(file, "%s\n", history_array[i%15]);
        }
        fclose(file);
    }
    
    insertSpaces(input);
    add_semicolon_at_end(input);
    char* delimiters = " \t\v\f\r";
    char** tokens = (char**)malloc(sizeof(char*)*MAX_TOKENS);
    for(int i=0;i<MAX_TOKENS;i++)
    {
        tokens[i] = (char*)malloc(sizeof(char)*MAX_TOKEN_LENGTH);
    }

    int token_count = 0;
    
    char *token = strtok(input, delimiters);
    while (token != NULL && token_count < MAX_TOKENS) 
    {
        tokens[token_count++] = token;
        token = strtok(NULL, delimiters);
    }
    execute(tokens,token_count,history_array,list);
}