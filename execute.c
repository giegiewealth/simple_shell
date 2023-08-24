/**
* execute_command - Execute a command.
* @command: The command to be executed
* This function takes a command string as input
* and executes it using
* the appropriate system call.
* It parses the command and its arguments,
* then attempts to execute it.
* Return: 0 on success, -1 on failure.
* void execute_command(const char command)
* char token = strtok((char )command, " ");
* {
* pid_t child_pid = fork();
* if (child_pid == -1)
* {
* perror("fork");
* leo_print("Error forking process.\n");
* exit(EXIT_FAILURE);
* }
* else if (child_pid == 0)
* {
* exelp(command, command, (char )NULL;
* perror("excelp");
* exit(EXIT_FAILURE);
* }
* else
* {
* wait(NULL);
* } 
*/

#include "shell.h"



void execute_command(const char *command)
{
    pid_t child_pid = fork();

    if (child_pid == -1) 
    {
        leo_print("Error forking process.\n");
        exit(EXIT_FAILURE);
    } 
    else if (child_pid == 0)
    {
        /**
	 * Child process
	 */

        /**
	 * Parse the command and its arguments
	 */

        char *args[128];
       /**
	* Maximum 128 arguments (adjust as needed)
	*/
        int arg_count = 0;

        char *token = strtok((char *)command, " ");
        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;
	/**
	 * Null-terminate the arguments array
	 */

        /**
	 * Execute the command
	*/
        execvp(args[0], args);

        /**
	 * If execvp fails, print an error message
	 */
        leo_print("Error executing command.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        /**
	 * Parent process
	 * */
        wait(NULL);
    }
}
