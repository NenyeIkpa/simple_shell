#ifndef SHELL_H_
#define _SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>

typedef struct llist
{
	char *dir;
	struct llist *next;
} path_llist;

int handle_args(char **iptr, char **argv);
void print_prompt(void);
void print_error(void);
path_llist *add_node(path_llist **head, const char *token);
path_llist *token_to_list(char **env);
char *search_path(path_llist **head, char *arg);
char *validate_access(path_llist **path, char *arg);
char *concatenate(char *a, char *b, char *c);

#endif
