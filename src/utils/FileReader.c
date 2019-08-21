#include "FileReader.h"

/*TODO: this check is not considering a case that the file name is in a sub-directory*/

int 		check_if_file_exists			(char *fullDirectory)
{
    printf("check 10 we're in check_if_file_exists, assume %s full dir\n", fullDirectory);
    if( access (fullDirectory, F_OK ) != -1 )
    {
        printf("check 11 able to access %s \n", fullDirectory);
        return 0;
    }

    else
    {
        return -1;
    }
}

char*		rename_file						(char *fileInitialName, char *fileExtension)
{
    char* fileNameWithExtension = "";
    int isRenamed = 0;

    printf("check 3 we're in rename_file, about to rename %s\n", fileInitialName);
    fileNameWithExtension = concat(fileInitialName, fileExtension);
    printf("check 4 %s\n", fileNameWithExtension);
    isRenamed = rename(fileInitialName,fileNameWithExtension);
    printf("check 5 %d\n",isRenamed);
    if (isRenamed == 0)
    {
        printf("check 6 %s\n",fileNameWithExtension);
        return fileNameWithExtension;
    }
    else
    {
        printf("check 7 %s\n",fileNameWithExtension);
        free(fileNameWithExtension);
        return fileInitialName;
    }
}

int 		open_or_create_file 			(FILE **pf, char* filepathwithextention)
{
    printf("check 9 about to open%s\n", filepathwithextention);

    if (check_if_file_exists(filepathwithextention) == -1)
    {
        printf("check 12 file does not exists, creating %s\n", filepathwithextention);
        *pf = fopen(filepathwithextention, "a+");
    }

    else
    {
        printf("check 13 file exists, opening %s\n", filepathwithextention);
        *pf = fopen(filepathwithextention, "r+");
    }

    if (*pf == NULL)
    {
        return -1;
    }

    return 0;
}

void doWhileFileHaveLines(FILE * file, void (*nextLineHandler)(char*)){
    char line[MAX_LINE_SIZE];
    printf("check 16 we're on doWhileFileHaveLines\n");
    while(fgets(line, sizeof(line), file))
    {
        printf("check 17 line %s read successfully.\n", line);
        nextLineHandler(line);
        printf("check done 17 \n");
    }
}


