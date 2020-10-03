// Разработать программу solution, которая осуществляет поиск 
// и подсчет числа процессов с именем genenv в системе Linux 
// на которой выполняется программа. 
// Пример вызова
// ./solution
// 13

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main()
{
    DIR *dp;
    struct dirent *ep;  
    long folderName = 0;
    char fileName[255];
    char *end = NULL;
    FILE *stat = NULL;
    char *lineptr = NULL;
	size_t length = 0;
    int counter = 0;

    dp = opendir ("/proc/");

    if (dp != NULL){
        while (ep = readdir (dp)){
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

                //printf("%s\n", lineptr);
                if(strstr(lineptr, "genenv")){
                    counter++;
                }

                fclose(stat);
            }
        }
        closedir (dp);
    }
    else{
        perror ("Couldn't open the directory");
    }

    printf("%d\n", counter);
	
	return 0;	
}