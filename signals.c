#include "headers.h"

void ping(char* pid_str,char* signal_number_str)
{
    pid_t pid = atoi(pid_str);
    if(pid==0)
    {
        perror("Invalid pid");
        return;
    }
    int sig_num = atoi(signal_number_str);
    sig_num%=32;
    int check = kill(pid,0);
    if(check == -1)
    {
        perror("Invalid pid");
        return;
    }

    int ret = kill(pid,sig_num);
    if(ret!=0)
    {
        perror("Could not ping given pid with required signal");
    }
    else
    {
        printf("Sent signal %d to process with pid %d\n",sig_num,pid);
    }
}

struct termios orig_termios;

void die(const char *s) {
    // perror(s);
    // exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

int input_in_rawmode()
{
    char c;
    // while (1) {
    setbuf(stdout, NULL);
    enableRawMode();
    input[0] = '\0';
    pt = 0;
    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        if (iscntrl(c))
        {
            if (c == 10)
            {
                printf("\n");
                break;
            }
            else if (c == 127)
            { // backspace
                if (pt > 0)
                {
                    if (input[pt - 1] == 9)
                    {
                        for (int i = 0; i < 7; i++)
                        {
                            printf("\b");
                        }
                    }
                    input[--pt] = '\0';
                    printf("\b \b");
                }
            }
            else if (c == 9)
            { // TAB character
                input[pt++] = c;
                for (int i = 0; i < 8; i++)
                { // TABS should be 8 spaces
                    printf(" ");
                }
            }
            else if (c == 4) // ctrl +d
            {
                printf("\n");
                exit(0);
            }
        }
        else
        {
            input[pt++] = c;
            printf("%c", c);
        }
    }
    disableRawMode();
    input[pt++] = '\0';

    
    return 0;
}