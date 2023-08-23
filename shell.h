#ifndef SHELL_H_
#define SHELL_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>

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

int handle_args(char **iptr, char **argv);
char *prgm_name;
char *arg;
void print_prompt(void);
void print_error(void);
void print_error_A(void);
void print_error_B(void);
path_llist *add_node(path_llist **head, char *token);
path_llist *token_to_list(char **env);
char *search_path(path_llist **head, char *arg);
char *validate_access(path_llist **path);
char *concatenate(char *a, char *b, char *c);
int _strlen(char *);
int _strcmp(char *, char *);
int _strncmp(char *, char *, size_t);
char *_strcpy(char *, char *);
char *_strcat(char *, char *);
char *_strdup(char *);
char *_strtok(char *, const char *);
void delete_list(path_llist *);

#endif
