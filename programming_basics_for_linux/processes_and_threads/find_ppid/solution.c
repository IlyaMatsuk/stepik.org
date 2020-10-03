#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	FILE *stat = fopen("/proc/self/stat", "r");
	if(stat == NULL){
		printf("Can't open stat-file\n");
		return -1;
	}
	
	char *lineptr = NULL;
	size_t length = 0;
	ssize_t readBytes = getline(&lineptr, &length, stat);	
	if(readBytes < 0){
		printf("Can't read file\n");
		free(lineptr);
		return -1;
	}
	
	char *line = strtok(lineptr, " ()");
	int i = 0;
	for(i = 0; i < 3; i++){
		line = strtok(NULL, " ()");
		if(line == NULL){
			break;
		}
	}
	printf("%s\n", line);
	return 0;	
}
