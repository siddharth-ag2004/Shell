#include "headers.h"

int x_flag = 0;
int time_interval;

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

  if(time_interval <= 0)
  {
    perror("Please enter positive integer time interval");
    return;
  }

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

    // char recent_path[PATH_MAX] = "/proc/loadavg";
    // FILE *file = fopen(recent_path, "r");
    // if (file == NULL) 
    // {
    //   perror("Error opening /proc/loadavg");
    //   return;
    // }

    // alarm(time_interval);
    // char pid[PATH_MAX];
    // char strtest[PATH_MAX];
    // fgets(strtest,PATH_MAX,file);
    // int field_count = sscanf(strtest, "%*f %*f %*f %*s %s", pid);
    
    // if (field_count == 1)
    //   printf("%s\n", pid);
    // else
    //   perror("Error reading PID");

    // // sleep(time_interval);
    // fclose(file);
  }
}