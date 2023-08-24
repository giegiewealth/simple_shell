#include "mainshell.h"

void read_command(char *command, size_t size)
{
if (fgets(command, size, stdin) == NULL)
{
if (feof(stdin))
{
print_dng("\n");
exit(EXIT_SUCCESS);
}
else
{
print_dng("Error while reading input.\n");
exit(EXIT_FAILURE);
}
}
command[strcspn(command, "\n")] = '\0';

/** Remove newline*/
}

/**
 * #include "mainshell.h"
* void read_command(char *command, size_t size)
* if (fgets(command, size, stdin) == NULL)
* {
* if (feof(stdin))
* {
* print_dng("\n");
* exit(EXIT_SUCCESS);
* }
*  else
* {
* print_dng("Error while reading input.\n");
* exit(EXIT_FAILURE);
* }
* }
* command[strcspn(command, "\n")] = '\0';
*/
/*
 * * Remove newline
*/
