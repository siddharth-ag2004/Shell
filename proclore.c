#include "headers.h"

void proclore(char* flag)
{
    char file_path[PATH_MAX];
    pid_t pid;
    int out_flag=1;
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
        out_flag=0;
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
                    const char *property = line + 7; 
                    const char *status_end = strchr(property, ' ');
                    if (status_end == NULL)
                    {
                        status_end = line + strlen(line);
                    }

                    int status_length = status_end - property;
                    char status[status_length + 1];

                    strncpy(status, property, status_length);
                    status[status_length] = '\0';

                    printf("process status: %s%s\n", status, (out_flag == 1) ? "+" : "");
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
        char executable_path[PATH_MAX];
        snprintf(executable_path, sizeof(executable_path), "/proc/%d/exe", pid);
        char resolved_path[PATH_MAX];
        ssize_t len = readlink(executable_path, resolved_path, sizeof(resolved_path) - 1);
        if (len != -1)
        {
            resolved_path[len] = '\0';
            printf("Executable path: %s\n", resolved_path);
        }
        else
        {
            printf("Failed to read executable path.\n");
        }
    
}