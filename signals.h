#ifndef __SIGNALS_H
#define __SIGNALS_H

void ping(char* pid_str,char* signal_number_str);
void die(const char *s);
void disableRawMode();
void enableRawMode();
int input_in_rawmode();

#endif