#include "headers.h"

char home_dir[PATH_MAX];
char cwd[PATH_MAX];
char last_dir[PATH_MAX];

int main()
{
    getcwd(cwd, sizeof(cwd));
    snprintf(home_dir, sizeof(home_dir), "%s", cwd);    
    // strcpy(cwd,"osn");
    while (1)
    {
        // strcpy(last_dir,cwd);
        prompt();
        char input[4096];
        fgets(input, 4096, stdin);

        input[strlen(input) - 1] = '\0';
    
        char *delimiters = " \t";
        char *tokens[MAX_TOKENS];
        int token_count = 0;
        
        char *token = strtok(input, delimiters);
        while (token != NULL && token_count < MAX_TOKENS) 
        {
            tokens[token_count++] = token;
            token = strtok(NULL, delimiters);
        }

        // for(int i=0;i<token_count;i++)
        // {
        //     printf("%s\n",tokens[i]);
        // }

        for(int i=0;i<token_count;i++)
        {
            if(strcmp(tokens[i],"warp")==0)
                i++;
            warp(tokens[i]);
        }
    }

    return 0;
}
