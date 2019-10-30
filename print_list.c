#include "common.h"

void print_list(slist *head)
{
	if(head == NULL)
	{
		printf("List empty\n");
	}
	else
	{
		while(head)
		{
			printf("[%d]  %s->%s\n",head->no,head -> array[1],head->array[2]);
			head = head -> link;
		}
		putchar('\n');
	}
	putchar('\n');
}

int insert_at_last(slist **head,char **cmd_array,int count)
{
	slist *new = malloc(sizeof(slist));

	if(new == NULL)
	{
		return -1;
	}
	//data insert
	//new -> data = data;
	new->array = calloc ((count+3),sizeof(char *));
	int i;
	new->array[0]=calloc(4,sizeof(char));
	strcpy(new->array[0],"pro");
	for(i = 1; i < count+2 ;i++)
	{
		new->array[i] = calloc(10,sizeof(char));

		strcpy(new->array[i],cmd_array[i]);

	}
	new->array[i] = (void *)0;
	new->no = count_jobs;

	//data insert
	new -> link = NULL;


	if(*head == NULL)
	{
		*head = new;
		return 0;
	}
	slist *temp = *head;
	while(temp -> link)
	{
		temp = temp -> link;
	}
	temp -> link = new;
	return 0;
}


int delete_at_last_fg(slist **head)
{
	if(*head == NULL)
	{
		printf("List is empty\n");
		return -1;
	}
	slist *temp = *head;
	slist *last;
         if(temp->link == NULL)
          { 
             *head = NULL;
           }
           else
          {
	while(temp->link)
	{
		last = temp;
		temp = temp -> link;
	}

	last->link = NULL;
        }
	pid_t fgid;
	fgid = fork();
	switch(fgid)
	{
		case 0:
			execvp(temp->array[1],temp->array+1);
			break;
		default:
			wait(0);
	}
	free(temp);
        count_jobs--;
	return 0;

}


int delete_at_last_bg(slist **head)
{
	
if(*head == NULL)
	{
		printf("List is empty\n");
		return -1;
	}
	slist *temp = *head;
	slist *last;
         if(temp->link == NULL)
          { 
             *head = NULL;
           }
           else
          {
	while(temp->link)
	{
		last = temp;
		temp = temp -> link;
	}

	last->link = NULL;
        }
	pid_t bgid;
	bgid = fork();
	switch(bgid)
	{
		case 0:
			execvp(temp->array[1],temp->array+1);
			break;
		default:
			;
	}
	free(temp);
        count_jobs--;
	return 0;
}
