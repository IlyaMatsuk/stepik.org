#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//create a method to compare values
int comp(const char *value1, const char *value2)
{
	if(*value1 < *value2){
		return 1;
	}
	else if(*value1 > *value2){
		return -1; 
	}
	else{
		return 0;
	}
}

int main(int c, char **v)
{
	struct sockaddr_in sockAddr;
	const int bufferSize = BUFSIZ * 10;
	const char exit[] = "OFF";
	char buffer[bufferSize];
	int nReadByte = 0;
	int clientSocket = 0;

	if(c < 2){
		printf("Invalid arguments\n");
	}

	int server = socket(AF_INET, SOCK_STREAM, 0);
	int port = atoi(v[1]);
	inet_aton("127.0.0.1", &sockAddr.sin_addr);
	sockAddr.sin_port = htons(port);
	sockAddr.sin_family = AF_INET;

	int error = bind(server, (struct sockaddr*) &sockAddr, sizeof(sockAddr));
	if(error){
		printf("Bind failed\n");
	}
	listen(server, 5);
	clientSocket = accept(server, NULL, NULL);

	while(1){
		nReadByte = recv(clientSocket, buffer, bufferSize, 0);
		if(!strcmp(buffer, exit)){			
			break;
		}
		if(nReadByte > 0){
			qsort(buffer, nReadByte, 1, comp);
			send(clientSocket, buffer, nReadByte, 0);
			memset(buffer, 0, nReadByte);
		}

	}
	close(clientSocket);
	return 0;
}
