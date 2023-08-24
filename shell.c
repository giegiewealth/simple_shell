#include "shell.h"
/**
* main - entry point
* description: passing prompts and commands
* Return: 0 always
*/

int main(void)
{
char command[120];

while (1) {
	display_prompt();
	read_command(command, sizeof(command));
	execute_command(command);
}
return (0);
}
