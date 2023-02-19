#include "main.h"

int command(char **argv){
    pid_t forkCheck;

    /**
    * initialize character strings to null values;
    */

    if (argv){
        char *instructShell;
        char *trueInstruct;
        instructShell = argv[0];

        /**
        * generate path for true instruction before execve() is called on it
        */
        trueInstruct = fetchPath(instructShell);

        forkCheck = fork();

        /**
         * child, 0: Madame Shell instance
         * parent 1: Bash shell
         *
         */
        if (forkCheck == -1)
        {
                perror("Unsuccessul");
                return 1;
        }

        if (forkCheck == 0)
        {
            /**
             * printf("child process created\n");
             */

            if(execve(trueInstruct, argv, NULL) == -1){
                perror("Error");
                exit(0);
            }
        }

        else
        {
            wait(NULL);
            /**
             * printf("arg %s\n",argv[0]);
             * printf("parent process still on\n");
             */

            return (0);
        }
    }
    /**
     * end of if(argv)
     * else is redundant
     */

    return (1);
}
