#include "mainshell.h"

void print_dng(const char *message)
{
    write(STDOUT_FILENO, message, strlen(message));
}
