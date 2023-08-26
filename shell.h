#ifndef SHELL_H_
#define SHELL_H_

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stddef.h>

/**
 * struct llist - linked list structure
 *
 * @dir: path to directory
 * @next: llist structure
 *
 */

typedef struct llist
{
	char *dir;
	struct llist *next;
} path_llist;

void handle_args(char **iptr, char **argv);
#define MAX_PATH_LENGTH 1024
extern char **environ;
size_t environ_size;
char *prgm_name;
char *arg;
char cmd_count;
int err_status;
void print_prompt(void);
void print_error(void);
void print_error_A(void);
void print_error_B(void);
path_llist *add_node(path_llist **head, char *token);
path_llist *token_to_list(void);
char *search_path(path_llist **head, char *arg);
int validate_access(char *path);
char *concatenate(char *a, char *b, char *c);
int _strlen(char *);
int _strcmp(char *, char *);
int _strncmp(char *, char *, size_t);
char *_strcpy(char *, char *);
char *_strcat(char *, char *);
char *_strdup(char *);
char *_strtok(char *, const char *);
void delete_list(path_llist *);
void _putc(char c);
void _puts(char *s);
void _putchar(char c);
void _putstring(char *s);
void handle_comments(char *input);
char *_realloc(char *buffer, size_t count);
int handle_builtins(char **argv, path_llist **head, char *line);
int _chdir(char **argv);
char *_getenv(char *envv);
void printenv(void);
int _putenv(char *new_env);
int _unsetenv(char *envv);
int _replaceenv(char *envv, char *replacant);
int _setenv(char *name, char *value, int overwrite);
char *_itoa(int num, char *str, int base);
void reverse_str(char *str);

#endif
