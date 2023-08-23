#ifndef SHELL_H_
#define SHELL_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
path_llist *add_node(path_llist **head, const char *token);
path_llist *token_to_list(char **env);
char *search_path(path_llist **head, char *arg);
char *validate_access(path_llist **path, char *arg);
char *concatenate(char *a, char *b, char *c);

#endif
