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

<<<<<<< HEAD
#define END_OF_FILE -2
#define EXIT -3
=======
/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

<<<<<<< HEAD
/* for convert_number() */
=======
/* for cnvrt_num() */
>>>>>>> 0bf15ae349fab10062ba030b1e6a25fc398050af
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
>>>>>>> 1f9bc2b6fea63b45ba82aa0b0697e60c5b58993a

/* Global environemnt */
extern char **environ;
/*Global program name */
static char *name;
/*Global history counter */
static int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
<<<<<<< HEAD
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;
=======
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

<<<<<<< HEAD
	char **cmd_buf;	  /* pointer to cmd ; chain buffer, for memory mangement */
=======
	char **cmd_buf;
/* pointer to cmd ; chain buffer, for memory mangement */
>>>>>>> 0bf15ae349fab10062ba030b1e6a25fc398050af
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;
<<<<<<< HEAD

#define INFO_INIT
{
	NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL,
		0, 0, 0
}
=======
#define INFO_INIT\
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}
>>>>>>> 0bf15ae349fab10062ba030b1e6a25fc398050af
>>>>>>> 1f9bc2b6fea63b45ba82aa0b0697e60c5b58993a

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
<<<<<<< HEAD
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);

/* Input Helpers */
void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* Error Handling */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int proc_file_commands(char *file_path, int *exe_ret);
#endif /* _SHELL_H_ */
=======
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
<<<<<<< HEAD
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
=======
int eputcharsc(char);
int _putdfdd(char c, int fd);
int _pristngd(char *str, int fd);
>>>>>>> 0bf15ae349fab10062ba030b1e6a25fc398050af

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
<<<<<<< HEAD
char *_strchr(char *, char);
=======
char *stchar_loc(char *, char);
>>>>>>> 0bf15ae349fab10062ba030b1e6a25fc398050af

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

<<<<<<< HEAD
/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);
=======
/* toem_con_atoi.c */
int intrtv(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _con_atoi(char *);

/* toem_errors1.c */
int __errorcatoiatoi(char *);
void prnt_errmsg(info_t *, char *);
int print_deci(int, int);
char *cnvrt_num(long int, int, int);
void rm_cmts(char *);

/* toem_builtin.c */
int _exitd(info_t *);
int _chngd(info_t *);
int _helpd(info_t *);

/* toem_builtin1.c */
int _hist(info_t *);
int _aliasd(info_t *);
>>>>>>> 0bf15ae349fab10062ba030b1e6a25fc398050af

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
<<<<<<< HEAD
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
=======
char *fetchenv(info_t *, const char *);
int _environd(info_t *);
int _setenv(info_t *);
int _myukwnenv(info_t *);
int popenv_lsts(info_t *);

/* toemfetchenv.c */
char **get_environ(info_t *);
int _ukwnenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *fetch_histf(info_t *info);
int wrt_hist(info_t *info);
int rdhist(info_t *info);
int bld_hislsts(info_t *info, char *buf, int linecount);
int renum_hist(info_t *info);
>>>>>>> 0bf15ae349fab10062ba030b1e6a25fc398050af

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
<<<<<<< HEAD
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
=======
int chain_delimeter(info_t *, char *, size_t *);
void check_chain_delimeter(info_t *, char *, size_t *, size_t, size_t);
int replace_aliasToke(info_t *);
int replace_varsToke(info_t *);
int replace_strings(char **, char *);

#endif

>>>>>>> 0bf15ae349fab10062ba030b1e6a25fc398050af
>>>>>>> 1f9bc2b6fea63b45ba82aa0b0697e60c5b58993a
