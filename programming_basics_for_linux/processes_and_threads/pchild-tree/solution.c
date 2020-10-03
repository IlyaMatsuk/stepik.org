#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int counter = 1;

void foo(int (*array)[2], int arraySize, int pid){
    int i = 0;
    for(i = 0; i < arraySize; i++){
        if(array[i][1] == pid){
            counter++;
            foo(array, arraySize, array[i][0]);
        }
    }
}

int main(int argc, char **argv)
{
    DIR *dp;
    struct dirent *ep;  
    long folderName = 0;
    char fileName[255];
    char *end = NULL;
    FILE *stat = NULL;
    char *lineptr = NULL;
	size_t length = 0;

    int i = 0;

    if(argc < 2){
        printf("Invalid arguments\n");
        return -1;
    }
    long pid = strtol(argv[1], &end, 10);

    dp = opendir ("/proc/");
    int processArray[1024][2];

    if (dp != NULL){
        for(i = 0; ep = readdir(dp); ){
            if(folderName = strtol(ep->d_name, &end, 10)){
                sprintf(fileName, "/proc/%lu/stat", folderName);
                stat = fopen(fileName, "r");
                if(stat == NULL){
                    printf("Can't open stat-file\n");
                    return -1;
                }

                ssize_t readBytes = getline(&lineptr, &length, stat);	
                if(readBytes < 0){
                    printf("Can't read file\n");
                    if(lineptr){
                        free(lineptr);
                    }
                    return -1;
                }
                processArray[i][0] = strtol(lineptr, &end, 10);//PID


                char *line = strtok(lineptr, " ()");
                int value = 0;
                // read only three value from file
                for(value = 0; value < 3; value++){
                    line = strtok(NULL, " ()");
                    if(line == NULL){
                        break;
                    }
                    if(value == 2){
                        processArray[i][1] = strtol(line, &end, 10);//PPID
                    }
                }
                i++;
                fclose(stat);
            }
        }
        closedir (dp);
    }
    else{
        perror ("Couldn't open the directory");
    }

    foo(processArray, i, pid);
    printf("%d\n", counter);
    /*sprintf(filename, "/proc/%lu/stat", pid);

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

    }*/

	return 0;	
}
