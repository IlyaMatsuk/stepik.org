#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    if(argc < 2){
        printf("Invalid arguments\n");
        return -1;
    }
    printf("%s\n", argv[1]);
    char filename[255];
    char *end = NULL;
    char *line = NULL;
    long pid = strtol(argv[1], &end, 10);
    sprintf(filename, "/proc/%lu/stat", pid);

    while(pid != 1){
        if(pid != strtol(argv[1], &end, 10)){
            sprintf(filename, "/proc/%lu/stat", pid);
        }
        FILE *stat = fopen(filename, "r");
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
        pid = strtol(line, &end, 10);
        printf("%lu\n", pid);

    }

	return 0;	
}
