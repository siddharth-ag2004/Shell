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
            printf(GREEN "<%s@%s:~> " RESET, username->pw_name,user.nodename);
        else
            printf(GREEN "<%s@%s:~ %s%s : %ds> " RESET, username->pw_name,user.nodename,WHITE,commandline_input,time_count);
    }
    else 
    {
        if(strstr(cwd, home_dir) == cwd) 
        {
            if(time_count==0)
                printf(GREEN "<%s@%s:%s~%s> " RESET, username->pw_name, user.nodename,BLUE, cwd + home_len);
            else
                printf(GREEN "<%s@%s:%s~%s %s%s : %ds> " RESET, username->pw_name, user.nodename,BLUE, cwd + home_len,WHITE,commandline_input,time_count);
        }
        else
        {
            if(time_count==0)
                printf(GREEN "<%s@%s%s: %s> " RESET, username->pw_name, user.nodename,BLUE,cwd);
            else
                printf(GREEN "<%s@%s:%s %s %s%s : %ds> ", username->pw_name, user.nodename,BLUE,cwd,WHITE,commandline_input,time_count);
        }
    }
    //     break;
    // }    
}
