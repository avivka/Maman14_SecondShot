#include "FileWriter.h"

void 		writeToFile		(char *filename, char * *buffer, int bufferLength)
{
	int 	i				= 0;
    FILE* 	file 			= fopen(filename, "w+");
    
    if(!file)
    {
        fprintf(stderr, "error could not create file: %s \n", filename);
        exit(0);
    }
    while (i < bufferLength)
    {
        fputs(buffer[i], file);
        
        fputs("\n", file);
        
        i++;
    }

    fclose(file);
}
