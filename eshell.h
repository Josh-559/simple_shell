#ifndef _ESHELL_H_
#define _ESHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>


/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* for command chaining */
#define CMD_NORMAL	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAINING	3

/* for convert_number() */
#define CONVERT_TO_SMALL	1
#define CONVERT_INTO_UNSIGNED	2

/* 1 if using system USE_GETLINE() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define File_History	".simple_shell_history"
#define HISTORY_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passdesc - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from USE_GETLINE containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@error_num: the error code for exit()s
 *@count_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buff: address of pointer to cmd_buff, on if chaining
 *@cmd_buff_type: CMD_type ||, &&, ;
 *@read_fd: the fd from which to read line input
 *@hist_count: the history line number count
 */
typedef struct passdesc
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_num;
	int count_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buff; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buff_type; /* CMD_type ||, &&, ; */
	int read_fd;
	int hist_count;
} desc_t;

#define desc_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(desc_t *);
} builtin_t;


/* toem_shloop.c */
int main_hsh(desc_t *, char **);
int builtin_command(desc_t *);
void find_command(desc_t *);
void fork_the_command(desc_t *);

/* toem_parser.c */
int is_command(desc_t *, char *);
char *dup_chars(char *, int, int);
char *command_path(desc_t *, char *, char *);

/* loopmain_hsh.c */
int loopmain_hsh(char **);

/* toem_errors.c */
void input_e(char *);
int _errorchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

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
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtokenizer(char *, char *);
char **strtokenizer2(char *, char);

/* toemrealloc_memory.c */
char *memory_set(char *, char, unsigned int);
void ffree(char **);
void *realloc_memory(void *, unsigned int, unsigned int);

/* toem_memory.c */
int free_pointer(void **);

/* toem_atoi.c */
int interactive(desc_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _string_to_int(char *);
void print_the_error(desc_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int fx_exit(desc_t *);
int change_dir(desc_t *);
int _myhelp(desc_t *);

/* toem_builtin1.c */
int _myhistory(desc_t *);
int _myalias(desc_t *);

/*toem_USE_GETLINE.c */
ssize_t get_input(desc_t *);
int _USE_GETLINE(desc_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getdesc.c */
void clear_desc(desc_t *);
void set_desc(desc_t *, char **);
void free_desc(desc_t *, int);

/* toem_environ.c */
char *get_the_env(desc_t *, const char *);
int _myenv(desc_t *);
int _my__setenv(desc_t *);
int _myun__setenv(desc_t *);
int populate_env_list(desc_t *);

/* toemget_the_env.c */
char **get_the_environ(desc_t *);
int _un__setenv(desc_t *, char *);
int __setenv(desc_t *, char *, char *);

/* toem_history.c */
char *get_history_of_file(desc_t *desc);
int write_history(desc_t *desc);
int read_history(desc_t *desc);
int build_history_list(desc_t *desc, char *buf, int linecount);
int renumber_history(desc_t *desc);

/* toem_lists.c */
list_t *add_to_node(list_t **, const char *, int);
list_t *add_to_node_end(list_t **, const char *, int);
size_t display_list_str(const list_t *);
int delete_node(list_t **, unsigned int);
void free_node(list_t **);

/* toem_lists1.c */
size_t legth_list(const list_t *);
char **returned_strings(list_t *);
size_t print_list(const list_t *);
list_t *first_node_starts_with(list_t *, char *, char);
ssize_t findd_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(desc_t *, char *, size_t *);
void check_chain(desc_t *, char *, size_t *, size_t, size_t);
int replace_alias(desc_t *);
int replace_vars(desc_t *);
int replace_string(char **, char *);

#endif
