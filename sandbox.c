#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/ucontext.h>

extern void readString(char *s, int r);

void signalFunc(int sig, siginfo_t *siginfo, void *ucp)
{

}


void init_sandbox()
{

}