#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80 /* The maximum length command*/
#define DELIMITERS " \t\n\v\f\r"


/**
 * @brief 清空 args
 * @param  args             My Param doc
 */
void refresh_args(char *args[])
{
    while (*args)
    {
        free(*args);  // avoid memory leak
        *args++ = NULL;
    }
}

/**
 * @brief Get the input object
 * @param  command
 * @return 0: invalid input; 1: valid
 */
int get_input(char *command)
{
    char input_buffer[MAX_LINE + 1];  /* 防止 input 为空, 把 command 给刷没了 */
    if(fgets(input_buffer, MAX_LINE+1, stdin) == 0) /* 比如文件为空 */
    {
        fprintf(stderr, "Failed to read input!\n");  // stderr 不存缓冲区, 直接输出
        return 0;
    }
    if(strncmp(input_buffer, "!!", 2) == 0)
    {
        if(strlen(command) == 0)
        {
            sprintf(stderr, "No command history");
            return 0;
        }
        return 1;
    }
    strcpy(command, input_buffer);
    return 1;
}


/**
 * @brief  spilt command into args
 * @param  args
 * @param  original_command
 * @return num of tokens
 */
size_t parse_input(char *args, char *original_command)
{
    size_t num = 0;
    char command[MAX_LINE + 1];
    strcpy(command, original_command);
    char *token = strtok(command, DELIMITERS);
    while (token != NULL)
    {
        args[num] = malloc(strlen(token) + 1);
        strcpy(args[num], token);
        num++;
        token = strtok(NULL, DELIMITERS);
    }
    return 0;    
}

void run_command()
{
    printf("run command");
}


int main(void)
{
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /*flag to determine whether to exit the program*/
    char command[MAX_LINE + 1]; /* raw command*/

    while (should_run)
    {
        printf("osh>");
        fflush(stdin);
        fflush(stdout); /* 清空输出缓存 */
        // 清空 args
        refresh_args(args);

        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) parent will invoke wait() unless command included &
         */

        // 没拿到输入
        if(get_input(command) == 0)
            continue;

        size_t args_num = parse_input(args, command);
        /* continue or exit */
        if(args_num == 0)  // empty input
        {
            printf("Please enter the command! (or type in \"exit\" to exit)\n");
            continue;
        }

        if(strcmp(args[0], "exit") == 0)
            break;
        
        /* run command */
        run_command();
    }
    return 0;
}
