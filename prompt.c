#include "headers.h"

void prompt() {
   struct utsname user;
    uname(&user);

    uid_t user_id = getuid();
    struct passwd *username = getpwuid(user_id);
  
    int home_len = strlen(home_dir);
    // printf("%s\n",home_dir);

    getcwd(cwd,sizeof(cwd));
    int cwd_len= strlen(cwd);
    if(strcmp(cwd,home_dir)==0)
    {
        if(time_count==0)
            printf("<%s@%s:~> ", username->pw_name,user.nodename);
        else
            printf("<%s@%s:~ %s : %ds> ", username->pw_name,user.nodename,commandline_input,time_count);
    }
    else 
    {
        if(strstr(cwd, home_dir) == cwd) 
        {
            if(time_count==0)
                printf("<%s@%s:~%s> ", username->pw_name, user.nodename, cwd + home_len);
            else
                printf("<%s@%s:~%s %s : %ds> ", username->pw_name, user.nodename, cwd + home_len,commandline_input,time_count);
        }
        else
        {
            if(time_count==0)
                printf("<%s@%s: %s> ", username->pw_name, user.nodename,cwd);
            else
                printf("<%s@%s: %s %s : %ds> ", username->pw_name, user.nodename,cwd,commandline_input,time_count);
        }
    }
    //     break;
    // }    
}
