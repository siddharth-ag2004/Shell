#ifndef HEADERS_H_
#define HEADERS_H_

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<sys/utsname.h>
#include<pwd.h>
#include<sys/types.h>
#include<linux/limits.h>
#include<string.h>
#include<libgen.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<ctype.h>
#include<dirent.h>
#include<time.h>
#include<grp.h>
#include<signal.h>
#include<termios.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 200

#define RED "\x1b[31m"
#define WHITE "\x1b[37m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"

#define perror(message) fprintf(stderr, RED "%s" RESET "\n", message)

extern char home_dir[PATH_MAX];
extern char cwd[PATH_MAX];
extern char last_dir[PATH_MAX];
extern char commandline_input[MAX_TOKEN_LENGTH];
extern int history_index;
extern int time_count;
extern char *input;
extern int pt;
extern int curr_fg;

#include "prompt.h"
#include "warp.h"
#include "list.h"
#include "pipe.h"
#include "redirect.h"
#include "pastevents.h"
#include "proclore.h"
#include "peek.h"
#include "seek.h"
#include "parse.h"
#include "activities.h"
#include "fg_bg.h"
#include "neonate.h"
#include "signals.h"
#include "headers.h"
#include "execute.h"

#endif