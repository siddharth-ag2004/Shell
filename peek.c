#include "headers.h"

int isflag(char* token)
{
    if(token[0]=='-' && (strlen(token)==2||(strcmp(token,"-la")==0)||(strcmp(token,"-al")==0)))
        return 1;
    return 0;
}

int cmpf_string(const void* a,const void* b)
{
    char* aa = *(char**)a;
    char* bb = *(char**)b;
    return strcasecmp(aa,bb);
}

void permissions(char *filepath) 
{
    // printf("%s\n",filepath);
    struct stat fileStat;
    if (stat(filepath, &fileStat) == -1) 
    {
        perror("Error getting file status");
        return;
    }

    mode_t mode = fileStat.st_mode;
    
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\t");
}

void peek(char* flag1 ,char* flag2 ,char* path)
{
    char** store_strings =  (char**)malloc(1000*sizeof(char*));         // GIVEN RANDON SIZE
    for(int i=0;i<1000;i++)
    {
        store_strings[i] = (char*)malloc(PATH_MAX*sizeof(char));
    }

    if(flag1==NULL && flag2==NULL)
    {
        struct dirent *d;
        if(path==NULL)
        {
            path = ".";
        }
        else if(path[0]=='-')
        {
            strcpy(path,last_dir);
        }
        else if(path[0]=='~')
        {
            strcpy(path,home_dir);
        }

        DIR *dr = opendir(path);
        if(dr==NULL)
        {
            perror("Error in opening directory");
            return;
        }

        int idx=0;
        while((d=readdir(dr))!=NULL)
        {
            // if(strcmp(d->d_name,".")==0 || strcmp(d->d_name,"..")==0)
            if(d->d_name[0]=='.')
                continue;
            strcpy(store_strings[idx++],d->d_name);
        }

        qsort(store_strings,idx,sizeof(char*),cmpf_string);

        for(int i=0;i<idx;i++)
        {
            printf("%s\n",store_strings[i]);
        }

        closedir(dr);
    }
    else if(flag1!=NULL)
    {
        if(strcmp(flag1,"-a")==0 && flag2==NULL)
        {
            struct dirent *d;
            if(path==NULL)
            {
                path = ".";
            }
            else if(path[0]=='-')
            {
                strcpy(path,last_dir);
            }
            else if(path[0]=='~')
            {
                strcpy(path,home_dir);
            }

            DIR *dr = opendir(path);
            if(dr==NULL)
            {
                perror("Error in opening directory");
                return;
            }

            int idx=0;
            while((d=readdir(dr))!=NULL)
            {
                strcpy(store_strings[idx++],d->d_name);
            }

            qsort(store_strings,idx,sizeof(char*),cmpf_string);

            for(int i=0;i<idx;i++)
            {
                printf("%s\n",store_strings[i]);
            }

            closedir(dr);
        }
        else if(strcmp(flag1,"-l")==0 || strcmp(flag1,"-la")==0 || strcmp(flag1,"-al")==0 || flag2!=NULL)
        {
            int a_flag=1;
            if(strcmp(flag1,"-l")==0)
            {
                a_flag=0;
            }
            if(flag2!=NULL)
            {
                a_flag=1;
            }
            struct dirent *d;
            if(path==NULL)
            {
                path = ".";
            }
            else if(path[0]=='-')
            {
                strcpy(path,last_dir);
            }
            else if(path[0]=='~')
            {
                strcpy(path,home_dir);
            }

            DIR *dr = opendir(path);
            if(dr==NULL)
            {
                perror("Error in opening directory");
                return;
            }

            int idx=0;
            while((d=readdir(dr))!=NULL)
            {
                if(d->d_name[0]=='.' && a_flag==0)
                    continue;
                strcpy(store_strings[idx++],d->d_name);
            }

            qsort(store_strings,idx,sizeof(char*),cmpf_string);

            for (int i=0;i<idx;i++) 
            {
                char* absolute_path_string = (char*)malloc(sizeof(char)*PATH_MAX); 
                sprintf(absolute_path_string, "%s/%s/%s", cwd, path, store_strings[i]);
                permissions(absolute_path_string);
                // permissions(store_strings[i]);

                struct stat fileStat;
                if (stat(absolute_path_string, &fileStat) < 0) 
                {
                    perror("Error in stat");
                    return;
                }
                
                printf("%lu\t", (unsigned long)fileStat.st_nlink);
                
                char *username = getenv("USER");
                printf("%s\t", username);
                struct group *gr = getgrgid(fileStat.st_gid);
                if (gr != NULL) 
                {
                    printf("%s\t", gr->gr_name);
                } 
                
                printf("%ld\t", fileStat.st_size);

                const char* timeStr = ctime(&fileStat.st_mtime);
                int year,date;
                char month[4], time[9] , day[10];
                sscanf(timeStr, "%s %s %d %5s %d",day,month,&date, time,&year);
                printf("%s %d %s\t",month,date,time);
                
                printf("%s\n", store_strings[i]);
            }
        }
    }   
    else
    {
        perror("Invalid flags\n");
    }    

}