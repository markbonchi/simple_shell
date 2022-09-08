#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* points to an array of strings called the "environment" */
extern char **environ;

/**
 * struct data - struct that contains relevant runtime data
 * @av: argument vector
 * @input: command line written by user
 * @args: token of the command line
 * @status: last status of the shell
 * @counter: lines count
 * @_environ: environment variable
 * @pid: process ID if the shell
 */

typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_sh;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: singe ;inked list to store separators
 */

typedef sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 */

typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - singlr linked list
 */

typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	sruct r_var_list *next;
} r_var;

/**
 * struct builtin_s - builtin struct for command args
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(data_sh *dsh);
} builtin_t;

/* aux_lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_list2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* aux_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
char _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
char _strdpn(char *s, char *accept);
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);
void rev_string(char *s);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_sh *dsh, char *input, int i, int bool);
int check_syntax_error(data_sh *dsh, char *input);

/* readline.c */
char *_readline(int *i_eof);

/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(data_sh *dsh);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_sh *dsh);
int split_commands(data_sh *dsh, char *input);
char **split_line(char *input);

/* rep_var.c */
void check_env(r_var **h, char *in, data_sh *dsh);
int check_vars(r_var **head, char *in, char *st, data_sh *dsh);
char *replace_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_sh *dsh);

/* getline.c */
void bring_line(char **lineptr, size_t, *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line.c */
int exec_line(data_sh *dsh);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_sh *dsh);
int check_error_cmd(char *dir, data_sh *dsh);
int cmd_exec(data_sh *dsh);


#endif
