#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int histry;

/**
* struct list_str - A new struct type defining a linked list.
* @dir: A directory path.
* @next: A pointer to another struct list_str.
*/
typedef struct list_str
{
char *dir;
struct list_str *next;
} list_t;

/**
* struct builtin_s - A new struct type defining builtin commands.
* @name: The name of the builtin command.
* @f: A function pointer to the builtin command's function.
*/
typedef struct built_in_str
{
char *name;
int (*f)(char **argv, char **front);
} builtin_t;

/**
* struct alias_str - A new struct defining aliases.
* @name: The name of the alias.
* @value: The value of the alias.
* @next: A pointer to another struct alias_str.
*/
typedef struct alias_str
{
char *name;
char *value;
struct alias_str *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t _getline(char **ln_ptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *path_dir_getter(char *path);
int execute(char **args, char **front);
void list_freer(list_t *head);
char *_itoa(int num);

/* Input Helpers */
void line_handler(char **line, ssize_t read);
void rplc_var(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int retv_args(char **args, char **front, int *exe_ret);
int init_arg(char **args, char **front, int *exe_ret);
int args_handler(int *exe_ret);
int args_checker(char **args);
void args_freer(char **args, char **front);
char **alias_rplcer(char **args);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dst, const char *source);
char *_strncat(char *dst, const char *source, size_t n);
char *_strcpy(char *dst, const char *source);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*built_in_getter(char *command))(char **args, char **front);
int sh_exit(char **args, char **front);
int sh_env(char **args, char __attribute__((__unused__)) **front);
int sh_setenv(char **args, char __attribute__((__unused__)) **front);
int sh_unsetenv(char **args, char __attribute__((__unused__)) **front);
int sh_cd(char **args, char __attribute__((__unused__)) **front);
int sh_alias(char **args, char __attribute__((__unused__)) **front);
int sh_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copyenv(void);
void envmnt_freer(void);
char **_getenv(const char *var);

/* Error Handling */
int print_error(char **args, int err);
char *err_env(char **args);
char *err_1(char **args);
char *err_2_exit(char **args);
char *err_2_cd(char **args);
char *err_2_sntx(char **args);
char *err_126(char **args);
char *err_127(char **args);

/* Linkedlist Helpers */
alias_t *alias_adder_end(alias_t **head, char *name, char *value);
void alias_list_freer(alias_t *head);
list_t *node_adder_end(list_t **head, char *dir);
void list_freer(list_t *head);

void all_helper(void);
void alias_helper(void);
void cd_helper(void);
void exit_helper(void);
void help_helper(void);
void envmnt_helper(void);
void set_envmnt_helper(void);
void unset_envmnt_helper(void);
void hist_helper(void);

int proc_file_comm(char *file_path, int *exe_ret);
#endif /* _SHELL_H_ */
