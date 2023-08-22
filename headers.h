#ifndef HEADERS_H_
#define HEADERS_H_

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include <sys/utsname.h>
#include <pwd.h>
#include <sys/types.h>
#include <linux/limits.h>
#include<string.h>
#include<libgen.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 200

extern char home_dir[PATH_MAX];
extern char cwd[PATH_MAX];
extern char last_dir[PATH_MAX];
extern int history_index;

#include "prompt.h"
#include "warp.h"
#include "list.h"
#include "pastevents.h"
#include "parse.h"

#endif