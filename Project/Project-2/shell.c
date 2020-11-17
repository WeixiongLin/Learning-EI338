#include<stdio.h>
#include<unistd.h>

#define MAX_LINE 80 /* The maximum length command*/


int get_input(char *command)
{
    char input_buffer[MAX_LINE + 1];  /* 防止 input 为空, 把 command 给刷没了 */
    if(fgets(input_buffer, MAX_LINE+1, stdin) == 0) /* 比如文件为空 */
    {
        fprintf(stderr, "Failed to read input!\n");
        return 0;
    }
    if()
    return 1;
}



int main(void)
{
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /*flag to determine whether to exit the program*/

    while (should_run)
    {
        printf("osh>");
        fflush(stdout); /* 清空输出缓存 */

        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) parent will invoke wait() unless command included &
         */

        char command[MAX_LINE + 1];
    }
    
    return 0;
}