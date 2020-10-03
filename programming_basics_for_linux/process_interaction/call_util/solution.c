#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    if(argc < 2){
        printf("Invalid arguments\n");
        return -1;
    }
	char utilName[255];
	snprintf(utilName, sizeof(utilName), "%s %s", argv[1], argv[2]);

	FILE* util = popen(utilName, "r");
	if(util == NULL){
		printf("can't open util:%s\n", utilName);
		return -1;
	}

	int ch = 0, counter = 0;	
	do
    {
      ch = fgetc(util);
      if (ch == '0'){
		  counter++;
	  } 
    } while (ch != EOF); // пока не конец файла
 
    fclose (util);

	printf("%d\n", counter);
    
	return 0;
}

