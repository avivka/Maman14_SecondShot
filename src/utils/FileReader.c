#include "FileReader.h"

int 		check_if_file_exists			(char *fullDirectory)
{
    if( access (fullDirectory, F_OK ) != -1 )
    {
        return 0;
    }

    else
    {
        return -1;
    }
}

char*		rename_file						(char *fileInitialName, char *fileExtension)
{
    char* 	fileNameWithExtension 			= "";
    int 	isRenamed 						= 0;

    
    fileNameWithExtension = concat(fileInitialName, fileExtension);
    
    isRenamed = rename(fileInitialName,fileNameWithExtension);
    
    if (isRenamed == 0)
    {
        return fileNameWithExtension;
    }
    
    else
    {
        free(fileNameWithExtension);
     
        return fileInitialName;
    }
}

int 		open_or_create_file 			(FILE **pf, char* filepathwithextention)
{
    if (check_if_file_exists(filepathwithextention) == -1)
    {
		printf("check creating new file \n");
		
        *pf = fopen(filepathwithextention, "w+");
    }

    else
    {
		printf("check opening the file \n");
		
        *pf = fopen(filepathwithextention, "a+");
    }

    if (*pf == NULL)
    {
        return -1;
    }

    return 0;
}

void 		doWhileFileHaveLines			(FILE * file, void (*nextLineHandler)(char*))
{
    char 	line[MAX_LINE_SIZE]				= "";
    while(fgets(line, sizeof(line), file))
    {
        nextLineHandler(line);
    }
}

/*void DoWhileFileHaveLines(char* filename, void (*nextLineHandler)(char*)){
    char line[MAX_LINE_SIZE] = "";
    FILE* fileToAssembler = NULL;
    int	counter = 1;
    int counter2 = 0;
    printf("check 16 we're on doWhileFileHaveLines\n");
    
    if (open_or_create_file(&fileToAssembler,filename) == 0)
	{
		while(fgets(line, sizeof(line), fileToAssembler))
		{
			
			if (fileToAssembler != NULL)
			{
				printf("check all good \n");
				
				printf("check 17 line %s read successfully.\n", line);
				nextLineHandler(line);
				printf("check done 17 %s\n", line);
				counter2++;
				
				printf("check counter = %d counter2 = %d \n", counter, counter2);
				
				if(counter == counter2)
				{
					counter++;
					counter2 = 0;
					if (fclose(fileToAssembler) == 0)
					{
						printf("check closed \n");
						
						if (open_or_create_file(&fileToAssembler,filename) == 0)
						{
							printf("check opened successfully \n");
						}
						
						else
						{
							printf("check problem with opening file \n");
						}
					}
					
					else
					{
						printf("check problem with closing file \n");
					}
				}
			}
			else
			{
				printf("check error!!!!! \n");
			}
			
		}
	}
}*/


