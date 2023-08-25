#include "headers.h"

char found_file[PATH_MAX];

int is_seek_flag(char* token)
{
    if(token[0]=='-' && ((strcmp(token,"-f")==0) || (strcmp(token,"-d")==0)||(strcmp(token,"-e")==0)))
        return 1;
    return 0;
}

void seek_rec(char* flag1, char* flag2, char* target, char* path,int* found)
{
    struct dirent *rec_d;
    DIR *rec_dr = opendir(path);
    
    if (rec_dr == NULL)
    {
        return;
    }
    else
    {
        while ((rec_d = readdir(rec_dr)) != NULL)
        {
            if (strcmp(rec_d->d_name, ".") == 0 || strcmp(rec_d->d_name, "..") == 0)
                continue;

            char sub_path[PATH_MAX];  
            snprintf(sub_path, sizeof(sub_path), "%s/%s", path, rec_d->d_name);
            
            struct stat entry_stat;
            if (lstat(sub_path, &entry_stat) == -1) 
            {
                perror("Error getting file/directory information");
                continue;
            }

            // if(isSubstring(target, rec_d->d_name))
            if(strncmp(target, rec_d->d_name,strlen(target))==0)
            {
                // printf("1");
                if((flag1 == NULL || (flag1[1] == 'f' && S_ISREG(entry_stat.st_mode)) || (flag1[1] == 'd' && S_ISDIR(entry_stat.st_mode))))
                {
                    if(S_ISDIR(entry_stat.st_mode))
                        printf(BLUE "%s/%s\n" RESET, path, rec_d->d_name);
                    else if(S_ISREG(entry_stat.st_mode))
                        printf(GREEN "%s/%s\n" RESET, path, rec_d->d_name);
                    else
                        printf("%s/%s\n", path, rec_d->d_name);                    
                    sprintf(found_file,"%s/%s", path, rec_d->d_name);
                    (*found)++;
                }
            }

            seek_rec(flag1, flag2, target, sub_path,found);
        }
        closedir(rec_dr);
    }
}

void seek(char* flag1, char* flag2, char* target, char* path)
{
    if(target==NULL)
    {
        perror("No target specified");
        return;
    }
    if (path == NULL)
    {
        path = ".";
    }

    DIR *dr = opendir(path);
    if (dr == NULL)
    {
        printf("Error in opening directory");
        return;
    }

    int found=0;

    struct dirent *d;
    while ((d = readdir(dr)) != NULL)
    {
        if (d->d_name[0] == '.')
            continue;

        // Construct the complete path for the current entry
        char full_path[PATH_MAX];  // Use stack-allocated array
        snprintf(full_path, sizeof(full_path), "%s/%s", path, d->d_name);
        
        struct stat entry_stat;
        if (lstat(full_path, &entry_stat) == -1) 
        {
            perror("Error getting file/directory information");
            continue;
        }

        if (strncmp(target, d->d_name,strlen(target))==0)
        {
            if((flag1 == NULL || flag1[1]=='e' || (flag1[1] == 'f' && S_ISREG(entry_stat.st_mode)) || (flag1[1] == 'd' && S_ISDIR(entry_stat.st_mode))))
            {
                if(S_ISDIR(entry_stat.st_mode))
                    printf(BLUE "./%s\n" RESET, d->d_name);
                else if(S_ISREG(entry_stat.st_mode))
                    printf(GREEN "%s\n" RESET, d->d_name);
                else
                    printf("./%s\n", d->d_name);
                sprintf(found_file,"./%s",d->d_name);
                found++;
            }
        }

        seek_rec(flag1, flag2, target, full_path,&found);
    }
    if(found==0)
    {
        perror("No match found!");
    }
    else if(found==1 && ((flag1!=NULL && flag1[1]=='e') || (flag2!=NULL && flag2[1]=='e')))
    {
        struct stat entry_stat;
        if (lstat(found_file, &entry_stat) == -1) 
        {
            perror("Error getting file/directory information");
            // return;
        }
        else if(S_ISDIR(entry_stat.st_mode))
        {
            chdir(found_file);
            strcpy(last_dir,cwd);
            getcwd(cwd, sizeof(cwd));
        }
        else if(S_ISREG(entry_stat.st_mode))
        {
            FILE* file = fopen(found_file, "r");
            if (file == NULL) 
            {
                perror("Missing permissions for task!");
                // return 1;
            }
            else
            {
                char ch;
                while ((ch = fgetc(file)) != EOF) 
                {
                    putchar(ch);
                }

                fclose(file);
            }
        }

    }

    closedir(dr);
}