#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/ucontext.h>

extern void readString(char *s, int r);
extern int main(int argc, char *argv[]);

struct sigaction sandbox;
void* ret_addr;

void sandbox_handler(int sig, siginfo_t *siginfo, void *ucp)
{
	if (siginfo->si_addr == readString) {
		mprotect((void*)((unsigned int)main & 0xfffffffffffff000), 1, PROT_READ | PROT_WRITE);			
		mprotect((void*)((unsigned int)readString & 0xfffffffffffff000), 1, PROT_READ | PROT_WRITE | PROT_EXEC);
		ret_addr = *(int *)(*(ucontext_t *)ucp).uc_mcontext.gregs[15];
	} else if (siginfo->si_addr == ret_addr) {
        mprotect((void*)((unsigned int)main & 0xfffffffffffff000), 1, PROT_READ | PROT_WRITE | PROT_EXEC);
        mprotect((void*)((unsigned int)readString & 0xfffffffffffff000), 1, PROT_READ | PROT_WRITE);
	} else {
        mprotect((void*)((unsigned int)main & 0xfffffffffffff000), 1, PROT_READ | PROT_WRITE | PROT_EXEC);
		printf("malicious buffer overflow detected, will exit!\n");
		exit(0);
	}
}

void init_sandbox()
{
	mprotect((void*)((unsigned int)readString & 0xfffffffffffff000), 1, PROT_READ | PROT_WRITE);
	memset(&sandbox,0,sizeof(struct sigaction));

	sandbox.sa_flags = SA_RESTART|SA_SIGINFO ;
	sandbox.sa_handler = sandbox_handler;

	sigemptyset(&sandbox.sa_mask);
	sigaddset(&sandbox.sa_mask,SIGSEGV);
	sigprocmask(SIG_UNBLOCK,&sandbox.sa_mask,NULL);	
	
	sigaction(SIGSEGV,&sandbox,NULL);	
}