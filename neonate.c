#include "headers.h"

int x_flag = 0;
int time_interval;

int kbhit() 
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

void PrintPid()
{
  char recent_path[PATH_MAX] = "/proc/loadavg";
  FILE *file = fopen(recent_path, "r");
  if (file == NULL) 
  {
    perror("Error opening /proc/loadavg");
    return;
  }

  char pid[PATH_MAX];
  char strtest[PATH_MAX];
  fgets(strtest,PATH_MAX,file);
  int field_count = sscanf(strtest, "%*f %*f %*f %*s %s", pid);
  fclose(file);
  if (field_count == 1)
    printf("%s\n", pid);
  else
    perror("Error reading PID");
}

void ALRMhandler(int signum)
{
  if(x_flag==0)
  {
    PrintPid();
    alarm(time_interval);
  }
}

void neonate(char* time_str)
{
  time_interval = atoi(time_str);

  if(time_interval <= 0 && strcmp(time_str,"0")!=0)
  {
    perror("Please enter positive integer time interval");
    return;
  }

  if(strcmp(time_str,"0")==0)
  {
    while(1)
    {
      PrintPid();
      if(kbhit())
      {
        char c;
        if (read(STDIN_FILENO, &c, 1) == 1) 
        {
          if (c == 'x') {
              x_flag=1;
              break;
          }
        }
      }
    }
  }
  else
  {
    signal(SIGALRM,ALRMhandler);
    alarm(time_interval);
    PrintPid();
    while(1)
    {
      char c;
      if (read(STDIN_FILENO, &c, 1) == 1) 
      {
        if (c == 'x') {
            x_flag=1;
            break;
        }
      }
    }
  }
}