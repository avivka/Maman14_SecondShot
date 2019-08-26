/* Includes 		*/

#include 	<stdio.h>
#include 	"../utils/FileReader.h"
#include    "SymbolsTable.h"

/* Definitions		*/

#define 	maxNumDecimalAddress 						1000
#define		char_to_ascii								48

/* Prototypes 	*/

int	 		from_binary_machine_code_to_fourth_base 	(int short, int*, char*);
char 		to_4_base									(char, char);
int			printSignToFile								(char*, FILE*);

