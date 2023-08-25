#include "headers.h"

void warp(const char* flag)
{
    char new_flag[PATH_MAX];
    int idx = 0;

    for (int i= 0;flag[i]!='\0';i++) 
    {
        if (flag[0] == '~') 
        {
            for (int j=0; home_dir[j]!='\0';j++) 
            {
                new_flag[idx++] = home_dir[j];
            }
        } 
        else 
        {
            new_flag[idx++] = flag[i];
        }
    }
    if(new_flag[0]=='-')
    {
        if(chdir(last_dir)==-1)                 
        {
            perror("Unable to change directory");
        }
        strcpy(last_dir,cwd);
        getcwd(cwd, sizeof(cwd));
        printf("%s\n",cwd);
    }
    else
    {
        strcpy(last_dir,cwd);
        new_flag[idx] = '\0'; 
        if (chdir(new_flag) == -1)               
        {
            perror("Unable to change directory");
        }
        getcwd(cwd, sizeof(cwd));
        printf("%s\n",cwd);
    } 
}
// chdir(home_dir);
