#include "main.h"

char *fetchPath(char *instructShell)
{
    /**
     * declare variables to store path string
     * and duplicate path string obtained with
     * getenv() function with strdup() and store.
     */

    char *path;
    char *duplPath;

    const char *delim;
    const char *prefix;
    const char *suffix;
    char *splitPath;
    char *fullPath;

    int instructLength;
    int splitSize;
    struct stat buffer;

    delim = ":";
    prefix = "/";
    suffix = "\0";

    path = getenv("PATH");

    if(path){
        duplPath = strdup(path);

     /**
      * OBJECTIVES
      * 1. obtain user input length
      * 2. tokenize input string
      * 3. insert '/' as prefix to input and '\0' as suffix
      * 4. test validity of generated string as a path using stat() function.
      */


        instructLength = strlen(instructShell);
        splitPath = strtok(duplPath,delim);

        while(splitPath != NULL)
        {
            splitSize = strlen(splitPath);
            fullPath = malloc(instructLength + splitSize + 2);

            strcpy(fullPath, splitPath);

            strcat(fullPath, prefix);
            strcat(fullPath, instructShell);
            strcat(fullPath, suffix);

            /**
            * 4 Validity check
            */

            if(stat(fullPath, &buffer) == 0){
                /**
                * return 0 - success
                * valid path selected
                */
                free(duplPath);
                return(fullPath);
            }
            else{
                free(fullPath);
                splitPath = strtok(NULL,delim);
            }
        }
    /**
     * path invalid, program continues
     * free duplicate string
     * for enough memory to run another check
     */

        free(duplPath);

    /**
     * last ditch check before program rerun
     * check if untokenized instructShell input
     * is a valid path in itself
     */

        if (stat(instructShell,&buffer)==0)
        {
            return(instructShell);
        }

        return (NULL);

    }

    return (NULL);
}
