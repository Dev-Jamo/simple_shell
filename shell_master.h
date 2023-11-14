#ifndef _SHELL_MASTER_
#define _SHELL_MASTER_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>

extern char **environ;

/* Read or write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* If 1 system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* Singly linked list structure */
/**
 * struct liststr - singly linked list node for strings
 * @num: numerical identifier (unused in current context)
 * @str: string data stored in the node
 * @next: pointer to the next node in the list
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/* Pseudo-arg structure for passing into a function */
/**
 * struct passinfo - structure for passing information to functions
 * @path: current working directory path
 * @arg: string generated from getline containing argument
 * @argv: array of strings made from arg
 * @argc: the argument count
 * @line_count: line count for errors
 * @err_num: error code of exit() calls
 * @linecount_flag: flag to count this line of input
 * @fname: program filename
 * @env: linked list local copy of environ
 * @history: history node
 * @alias: alias node
 * @environ: custom mod copy of environ from linked list env
 * @env_changed: flag indicating if the environment was changed
 * @status: return status of the last executed command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: file descriptor from which to read line input
 * @histcount: history line number count
 */
typedef struct passinfo
{
	char *path;
	char *arg;
	char **argv;
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
	char **cmd_buf; /* Points to cmd; chain buffer for memory mgmt */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT         \
{                        \
	NULL, NULL, NULL, 0, 0, 0, 0, NULL, \
	NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0 \
}

/* Builtin command structure */
/**
 * struct builtin - structure representing a built-in command and its handler
 * @type: string identifying the built-in command
 * @func: function pointer to the handler for the built-in command
 */
typedef struct builtin
{	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Function declarations */
char *path;
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int loophsh(char **);
int _eputchar(char);
void _eputs(char *);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);
char *starts_with(const char *, const char *);

void _puts(char *);
int _putchar(char);
char *_strdup(const char *);
char *_strcpy(char *, char *);

char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

char **strtow2(char *, char);
char **strtow(char *, char *);

void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

int bfree(void **);
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);

int _erratoi(char *);
int print_d(int, int);
void remove_comments(char *);
void print_error(info_t *, char *);
char *convert_number(long int, int, int);

int _mycd(info_t *);
int _myexit(info_t *);
int _myhelp(info_t *);

int _myhistory(info_t *);
int _myalias(info_t *);

void sigintHandler(int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);

void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *_getenv(info_t *, const char *);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int renumber_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);

void free_list(list_t **);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);

size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);

int replace_vars(info_t *);
int replace_alias(info_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

#endif


