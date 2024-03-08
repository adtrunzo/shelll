#include "sh.h"
#include <signal.h>
#include <stdio.h>

void sig_handler(int signal); 

int main( int argc, char **argv, char **envp )
{
  //signal(SIGINT, SIG_IGN);
  //signal(SIGTSTP, SIG_IGN);
  /* put signal set up stuff here */

   printf("Parent pid: %d\n", getpid());
  return sh(argc, argv, envp);
}

void sig_handler(int signal)
{
  if(!kill(-pid, 0)){
	  kill(-pid, signal);
  }
}

