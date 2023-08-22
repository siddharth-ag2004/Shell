#include "headers.h"

void proclore(char* flag)
{
    char file_path[PATH_MAX];
    pid_t pid;
    if(flag == NULL)
    {
        char default_path[PATH_MAX] = "/a.out";
        sprintf(file_path,"%s%s",home_dir,default_path);
        // printf("%s\n",file_path);
        pid = getpid();
    }
    else
    {
        pid = atoi(flag);
    }
        //PID
        printf("pid : %d\n", pid);

        //STATUS
        char proc_status_path[PATH_MAX];
        snprintf(proc_status_path, sizeof(proc_status_path), "/proc/%d/status" ,pid);
        
        size_t vm_size;

        FILE* status_file = fopen(proc_status_path, "r");
        if (status_file != NULL) 
        {
            char line[256];
            while (fgets(line, sizeof(line), status_file)) 
            {
                if (strncmp(line, "State:", 6) == 0) 
                {
                    char status[8];
                    sscanf(line + 7, "%s", status);

                    printf("process status : %s\n", status);
                }
                if(strncmp(line, "VmSize:",7)==0) 
                {
                    sscanf(line + 7, "%lu", &vm_size); 
                }
            }
            fclose(status_file);
        } 
        else 
        {
            printf("Failed to open /proc/%d/status\n", pid);
        }

        //GROUP
        pid_t pgid = getpgid(pid);
        printf("Process Group : %d\n", pgid);
        printf("Virtual memory : %lu\n", vm_size);
        // printf("Executable path : %s\n", file_path);
    
}