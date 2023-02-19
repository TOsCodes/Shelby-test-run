#include "main.h"

int main(int st, char **argv)
{
    size_t ln = 2;
    ssize_t chrCount;
    int io;
    int c;
    int chopNumber;
    int exeatCard;


    char *exite;
    char *chopped;
    char *duplicate;
    char *lineBufPtr;

    const char *delimiter = " \n";
    char *shellprompt = "\n:-| Madame $helby: ";
    (void)st;

    lineBufPtr = malloc(sizeof(char)*ln);
/**
 * char *lineBufPtr = NULL;
 * Madame Shelby shall handle her own memory allocation, thank you very much!
 */

    io = 1;
    chopNumber = 0;

while(io){
        printf("%s",shellprompt);
        chrCount = getline(&lineBufPtr,&ln,stdin);
 /**
  * filtering user inputs
  */
        if (chrCount==-1){
            printf(":-} Madame $helby will see you later... Goodbye.\n");
            return (-1);
        }

        duplicate = malloc(sizeof(char)*chrCount);
        if (duplicate==NULL){
            perror("tsh: memory allocation error");
            return(-1);
        }
/**
 * user inputs valid, proceed to duplicate
 *
 */
        strcpy(duplicate, lineBufPtr);

/**
 * initial user input string can then be chopped up
 */
        chopped = strtok(lineBufPtr, delimiter);
        while (chopped != NULL){
            chopNumber++;
            chopped = strtok(NULL, delimiter);
        }
        chopNumber++; /**accounts for index 0*/

/**
 * create array of suitable size (chopNumber obtained) to store chopped pieces
 */
        argv = malloc(sizeof(char *)*chopNumber);

/**
 * Objectives
 *  0. tokenize duplicate
 *  1. allocate space-sizes within array index for each chopped piece
 *  2. and copy string value of each current instance to them.
 */
        chopped = strtok(duplicate, delimiter);
    /**initiates new chop and holds most freshly chopped piece of duplicate*/

        for(c = 0; chopped != NULL; c++){
            argv[c]= malloc(sizeof(char)*strlen(chopped)); /** 1*/
            strcpy(argv[c], chopped); /** 2 (current instance)*/

        /**
         * continue strtok from after first chop
         * and continue sequential chops
         *
         * (create subsequent instance)
         */
            chopped = strtok(NULL, delimiter);
        }
            argv[c] = NULL; /**account for last index;*/

        /**
         * user option to exit Madame $helby
         */

        exite = "exit";
        exeatCard = strcmp(lineBufPtr, exite);

        if(exeatCard==0)
        {
            printf(":-} Madame $helby says Ciao!\n");
            argv[0] = "exit";
            return (0);
        }
/**
 * accept user input as argument and execute if valid
 */
        command(argv);
    }
/**
 * tidy up your work space
 */
    free(lineBufPtr);
    free(duplicate);

    return (0);
}
