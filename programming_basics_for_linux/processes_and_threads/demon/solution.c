#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo)
{
    printf("%d\n", getpid());
    if(signo == SIGURG){
        raise(SIGTERM);
    }
}

int main(int argc, char **argv)
{
    fclose(stdout);

    int _pid = fork();
    if(!_pid){
        signal(SIGURG, handler);
    }
    while(1){
        sleep(1);
    }
	return 0;	
}
