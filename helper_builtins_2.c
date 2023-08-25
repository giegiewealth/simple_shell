#include "shell.h"

void envmnt_helper(void);
void set_envmnt_helper(void);
void unset_envmnt_helper(void);
void hist_helper(void);

/**
* envmnt_helper - Displays information on the sh builtin command 'env'.
*/
void envmnt_helper(void)
{
char *msg = "env: env\n\tPrints the current environment.\n";

write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
* set_envmnt_helper - Displays information on the sh builtin command 'setenv'.
*/
void set_envmnt_helper(void)
{
char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

write(STDOUT_FILENO, msg, _strlen(msg));
msg = "environment variable, or modifies an existing one.\n\n";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "\tUpon failure, prints a message to stderr.\n";
write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
* unset_envmnt_helper - Displays information on the sh builtin command
* 'unsetenv'.
*/
void unset_envmnt_helper(void)
{
char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

write(STDOUT_FILENO, msg, _strlen(msg));
msg = "environmental variable.\n\n\tUpon failure, prints a ";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "message to stderr.\n";
write(STDOUT_FILENO, msg, _strlen(msg));
}
