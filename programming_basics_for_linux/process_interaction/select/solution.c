#include <fcntl.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>


int main(){
    int fds[2];
    char buffer[4096];
    int i = 0, readData = 0, result = 0, maxfd = 0;
    fd_set watchset;
    fd_set inset;

    if((fds[0] = open("in1", O_RDONLY | O_NONBLOCK)) < 0){
        perror("can't open in1-channel");
    }

    if((fds[1] = open("in2", O_RDONLY | O_NONBLOCK)) < 0){
        perror("can't open in2-channel");
    }

    FD_ZERO(&watchset);
    FD_SET(fds[0], &watchset);
    FD_SET(fds[1], &watchset);
    
    maxfd = fds[0] > fds[1] ? fds[0] : fds[1];

    while(FD_ISSET(fds[0], &watchset) || FD_ISSET(fds[1], &watchset)){
        inset = watchset;
        if(select(maxfd +1, &inset, NULL,NULL,NULL) < 0){
            perror("select error");
            return 1;
        }

        for(i = 0; i < 2; i++){
            if(FD_ISSET(fds[i], &inset)){
                readData = read(fds[i], buffer, sizeof(buffer) - 1);
                if(readData < 0){
                    perror("read error");
                    return 1;
                }
                else if(!readData){
                    close(fds[i]);
                    FD_CLR(fds[i], &watchset);
                }
                else{
                    buffer[readData] = '\0';
                    result += atoi(buffer);
                }
            }
        }
    }

	printf("%d\n", result);
    return 0;
}