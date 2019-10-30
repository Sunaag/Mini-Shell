#ifndef COMMON_H
#define COMMON_H

#include <unistd.h>
#include <fcntl.h>             
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

char buff[80];
char cmd_buff[80];
char shell_buff[80];
char prompt_buff[80];
char path_buff[80];
typedef struct
{
	char system_calls[3][6];
	char process[4][6];
	char echo_fam[3][7];
}check_cmd;
int ret_val;
check_cmd ch_cmd={"cd","pwd","mkdir",
	"ls","sleep","wc","grep",
	"$$","$?","$SHELL"};


pid_t pid;
typedef void (*sighandler_t)(int);
int compare(char **cmd_buff);
int execute_system_call(int cmd_cmp,char **cmd_array);
int execute_process(int cmd_cmp,char **cmd_array,int count);
int execute_echo_fam(int cmd_cmp,char **cmd_array);
int npipe(int argcc,char **argvc);

typedef struct node
{
	char **array;
	int no;
	struct node*link;
}slist;

void print_list(slist *head);
int insert_at_last(slist **head,char **cmd_array,int count);
int delete_at_last_fg(slist **head);
int delete_at_last_bg(slist **head);

int m;
int count_jobs;

#endif
