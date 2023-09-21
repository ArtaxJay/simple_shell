#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>



/* SYMBOLIC NAMES/CONSTANTS TO WRITE AND READ CLIP_BUFFERS --- SHELL LITTLE WINDOW STORAGE */
#define WRITE_BUFFER_SIZES 1024
#define READ_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* SYMBOLIC NAMES/CONSTANTS TO CHAIN COMMANDS */
#define COMMAND_NORMAL	0
#define COMMAND_LOGICAL_OR		1
#define COMMAND_LOGICAL_AND		2
#define COMMAND_CHAINED	3

/* SYMBOLIC NAMES/CONSTANTS TO CONVERT NUMBERS */
#define CONVERT_TO_LOWERCASE	1
#define CONVERT_FROM_UNSIGNED	2

/* CONSTANTS FOR GETLINE() SYS CALL AND SHELL HISTORY CAPACITY */
#define STRTOK_USED 0
#define GETLINE_USED 0
#define MAXIMUM_HISTORY_NUMBER	4096
#define FILE_HISTORY	"shell_history"

extern char **environment_variables;


/**
 * struct liststring - structured singly linked list with two variables
 * @num: this is the field number
 * @str: this variable will hold a string
 * @next: this variable will point to the next node
 */

typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} lists_t;

/**
 *struct pass_info_struct - this struct contains pseudo-arguements to be passed into functions,
 *		that will allow a uniform prototype for the functions pointer struct
 *@arg: arg hold strings that will be generated from getline() call
 *@argv: array arg of strings generated from arg parameter
 *@path: path var that holds string for the current command, options and signals
 *@argc: the arg counts the number of parameters passed
 *@line_count: this arg counts errors
 *@err_num: err_num holds error codes for terminating/exit()
 *@linecount_flag: signals the number of line counts
 *@fname: this names the program filename
 *@env: stores the linked-list of local copy of the environment variables
 *@environ: stores the custom-modified copy of the environment from the Locals
 *@history: arg stores the history node of a particular command
 *@alias: arg stores the alias node of a particular command
 *@env_changed: Turns on if any of the environment vars was changed
 *@status: stores the status returned by the last executed command
 *@cmd_buf: holds the address of pointers to command buffer, and turns on if chaining
 *@cmd_buf_type: command buffer types: logical "or" ||, logical "and" &&, ;
 *@readfd: reads line input from fd of the standard library
 *@histcount: holds the number history line counted
 */

typedef struct pass_info_struct
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	lists_t *env;
	lists_t *history;
	lists_t *alias;
	char **environment_variables;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} information_t;

#define INFORMATION_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtins - will contain builtin strings and other functions related
 *@type: builtin command flag for signalling
 *@func: func
 */

typedef struct builtins
{
	char *type;
	int (*func)(information_t *);
} builtins_tbls;


/* header statements for parsers.c */
char *search_path(information_t *, char *, char *);
int is_command(information_t *, char *);
char *duplicate_chars(char *, int, int);

/* the only func in loopshellhsh.c */
int loopshell(char **);

/* the header funcs in errors.c */
int _eputcharr(char);
int _putsfinds(char *str, int fd);
void _eeputts(char *);
int _putsfnd(char c, int fd);

/* the header statement for the file getenv.c */
char **get_envment(information_t *);
int _remenvvariable(information_t *, char *);
int _initnewvar(information_t *, char *, char *);

/* header statements for funcs in _string.c */
char *_concatstr(char *, char *);
int _compstrs(char *, char *);
char *haystack_needle(const char *, const char *);
int _len_of_str(char *);

/* header functs for exits.c */
char *_add_two_strs(char *, char *, int);
char *_copy_strns(char *, char *, int);
char *_loc_char(char *, char);

/* the header for functions in _string1.c */
char *_duplic_string(const char *);
void _pout_std(char *);
int _ptchars(char);
char *_strscopier(char *, char *);

/* header statement for functions inside builtin.c */
int _chgcurdir(information_t *);
int _chngdir(information_t *);
int _killshell(information_t *);

/* the header funcs for tokenizer.c */
char **splitstrs(char *, char *);
char **splitstrns(char *, char);

/* header for functions inside realloc.c */
void *_my_realloc(void *, unsigned int, unsigned int);
char *_memconstbyte(char *, char, unsigned int);
void disectfree(char **);

/* the only funtion inside the memory.c file */
int freepts(void **);

/* header statement for function in errors1.c */
int _str_to_int(char *);
char *con_nums(long int, int, int);
void prnt_err_msg(information_t *, char *);
void rem_commts(char *);
int prnt_dec_num(int, int);

/* header functions inside _atoi.c */
int _conv_str_int(char *);
int interacshell(information_t *);
int chk_for_delim(char, char *);
int _chk_for_alpha(int);

/* the header for builtin1.c */
int _mimicslibalias(information_t *);
int _lsthistory(information_t *);

/*the header function for getline.c file */
int _myverofgetline(information_t *, char **, size_t *);
ssize_t gets_line(information_t *);
void handlesignals(int);

/* header declaration for history.c */
int rd_hist(information_t *info);
int wrt_hist(information_t *info);
char *gt_hist_fle(information_t *info);
int chng_hist_num(information_t *info);
int add_entry_tohist(information_t *info, char *buf, int linecount);


/* header statement for getinfo.c file */
void fr_info_struct(information_t *, int);
void init_info_struct(information_t *, char **);
void kill_info_struct(information_t *);

/* header declaration for lists.c */
int del_dgiven_node(lists_t **, unsigned int);
void fr_all_node_lists(lists_t **);
lists_t *add_nd_to_list_end(lists_t **, const char *, int);
lists_t *add_nd_to_list_start(lists_t **, const char *, int);
size_t prnt_strelem_of_list(const lists_t *);


/* header statement for environ.c file */
int _initenvvar(information_t *);
int _prntcurenvvar(information_t *);
int add_to_env_lst(information_t *);
int _remenvvar(information_t *);
char *_gtenvvarval(information_t *, const char *);

/* header statements for loop.c */
void find_command_path(information_t *);
int finds_cmds_builtins(information_t *);
void forks_exec_cmd(information_t *);
int shellhsh(information_t *, char **);

/* header statement for lists1.c file */
ssize_t gt_index_of_nodes(lists_t *, lists_t *);
size_t len_of_lnkd_list(const lists_t *);
lists_t *nd_with_prefix_start(lists_t *, char *, char);
char **ret_array_of_strs(lists_t *);
size_t prnt_all_elem_lst(const lists_t *);

/* header declaration for vars.c file */
int repl_strngs(char **, char *);
int chck_chain_delim(information_t *, char *, size_t *);
int repl_vars_tok_strs(information_t *);
void chks_for_chain_status(information_t *, char *, size_t *, size_t, size_t);
int repl_tork_alias(information_t *);

#endif
