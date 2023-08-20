#include "headers.h"

void prompt() {
   struct utsname user;
    uname(&user);

    uid_t user_id = getuid();
    struct passwd *username = getpwuid(user_id);

    // getcwd(cwd, sizeof(cwd));
    // snprintf(home_dir, sizeof(home_dir), "%s", cwd);    
    int home_len = strlen(home_dir);
    // printf("%s\n",home_dir);

    // while(1)
    // {
    strcpy(last_dir,cwd);
    // printf("last_dir:%s\n",last_dir);
    getcwd(cwd,sizeof(cwd));
    int cwd_len= strlen(cwd);
    if(strcmp(cwd,home_dir)==0)
        printf("<%s@%s:~>\n", username->pw_name,user.nodename);
    else 
    {
        if(strstr(cwd, home_dir) == cwd) 
        {
            // printf("entered\n");
            printf("<%s@%s:~%s>\n", username->pw_name, user.nodename, cwd + home_len);
        }
        else
        {
            printf("<%s@%s: %s>\n", username->pw_name, user.nodename,cwd);
        }
    }
    //     break;
    // }    
}
