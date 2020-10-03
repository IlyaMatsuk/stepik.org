#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static int usr1Counter = 0;
static int usr2Counter = 0;

void handler(int signalNumber)
{
    if(signalNumber == SIGUSR1){
        usr1Counter++;
    }
    else if(signalNumber == SIGUSR2){
        usr2Counter++;
    }
    else if(signalNumber == SIGTERM){
        printf("%d %d\n", usr1Counter, usr2Counter);
        fflush (stdout);
        _exit(0);
    }
}

int main()
{
    if(signal(SIGUSR1, handler) == SIG_ERR){
        printf("error SIGUSR1\n");
    }
    if(signal(SIGUSR2, handler) == SIG_ERR){
        printf("error SIGUSR2\n");
    }
    if(signal(SIGTERM, handler) == SIG_ERR){
        printf("error SIGTERM\n");
    }
    while(1){
        sleep(1);
    }
    return 0;
}