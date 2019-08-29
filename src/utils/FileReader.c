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
		free (fileNameWithExtension);
		
        return fileInitialName;
    }
}

int 		open_or_create_file 			(FILE **pf, char* filepathwithextention)
{
    if (check_if_file_exists(filepathwithextention) == -1)
    {

		
        *pf = fopen(filepathwithextention, "w+");
    }

    else
    {

		
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
    char 	line[MAX_LINE_SIZE+1]				= "";

    while(fgets(line, sizeof(line), file))
    {

        if (strlen(line) == MAX_LINE_SIZE && !(isContainsChar(line,'\n')))
        {
            currentLine++;
            ERROR_PROGRAM(("line is longer then 80 characters."));
            while(fgets(line, sizeof(line), file))
            {
                if (isContainsChar(line,'\n'))
                {
                    break;
                }
            }
        }
        else
        {
            nextLineHandler(line);
            currentLine++;
        }

    }
}

int			deleteFile						(char* filepath, char* filextention)
{
	char*		fileFullPath				= "";
	
	fileFullPath = concat(filepath, filextention);
				
	if (check_if_file_exists(fileFullPath) == 0)
	{
		remove(fileFullPath);
	}

	free(fileFullPath);

	return 0;
}


