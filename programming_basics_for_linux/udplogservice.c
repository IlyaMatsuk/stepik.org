#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int c, char **v)
{
	struct sockaddr_in sockAddr;
	if(c < 2){
		printf("Invalid arguments\n");
	}

	int server = socket(AF_INET, SOCK_DGRAM, 0);
	int port = atoi(v[1]);
	inet_aton("127.0.0.1", &sockAddr.sin_addr);
	sockAddr.sin_port = htons(port);
	sockAddr.sin_family = AF_INET;

	int error = bind(server, (struct sockaddr*) &sockAddr, sizeof(sockAddr));
	if(error){
		printf("Bind failed\n");
	}
	
	const int bufferSize = BUFSIZ * 10;
	const char exit[] = "OFF\n";
	char buffer[bufferSize];
	int nReadByte = 0;
	while(1){
		nReadByte = read(server, buffer, bufferSize);
		if(strcmp(buffer, exit)){
			printf("%s\n", buffer);
			memset(buffer, 0, nReadByte);
		}
		else{
			break;
		}
	}
	return 0;
}
