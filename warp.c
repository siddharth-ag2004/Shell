#include "headers.h"

void warp(const char* flag)
{
    // printf("pop\n");
    if(strcmp(flag,"~")==0)
    {
        chdir(home_dir);
        strcpy(cwd,home_dir);
        printf("%s\n",home_dir);
    }
    if(strcmp(flag,".")==0)
    {
        chdir(cwd);
        printf("%s",cwd);
    }
    if(strcmp(flag,"..")==0)
    {
        // printf("cwd : %s\n",cwd);
        // printf("yess\n");
        char parent_dir[PATH_MAX];
        strcpy(parent_dir, cwd); 
        char* parent_path = dirname(parent_dir);

        chdir(parent_path);
        strcpy(cwd,parent_path);
        printf("%s\n",cwd);
        // printf("parentpath : %s\n",parent_path);
    }
    if(strcmp(flag,"-")==0)
    {
        chdir(last_dir);
        strcpy(cwd,last_dir);
        // printf("last: %s\n",last_dir);
    }
}
// chdir(home_dir);
