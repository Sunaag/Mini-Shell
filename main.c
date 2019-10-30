#include "common.h"
#include "functions.c"
#include "print_list.c"


void signal_handler(int num)
{
	kill(pid,SIGKILL);
	if((num = SIGTSTP) && (cmd_buff[0] != 0))
	{
		count_jobs++;
		m = 1;
	}
}

int main()
{
	system("clear");
	char **cmd_array;
	getcwd(buff,80);
	getcwd(shell_buff,80);
	slist *head = NULL;

	//signal ignore
	signal(SIGINT,signal_handler);
	signal(SIGQUIT,signal_handler);
	signal(SIGTSTP,signal_handler);
	//signal ignore

	while(1)
	{
		printf("%s:",buff);
		scanf("\n%[^\n]s",cmd_buff);

		printf("%s\n",cmd_buff);
		char *temp = cmd_buff;



		int count = 0;
		while(*temp)
		{
			if(*temp == ' ')
			{
				count++;
			}
			temp++;
		}

		printf("%d",count+1);

		char *tem_space=cmd_buff;
		char *tem1_space = cmd_buff;
		cmd_array = calloc ((count+3),sizeof(char *));
		int i;
		cmd_array[0]=calloc(4,sizeof(char));
		strcpy(cmd_array[0],"pro");
		for(i = 1; i < count+2 ;i++)
		{
			cmd_array[i] = calloc(10,sizeof(char));
			tem1_space = tem_space;
			while(*tem_space != ' ' && *tem_space != '\0')
			{	
				tem_space++;
			}
			if(*tem_space != '\0')
			{
				*tem_space = '\0';
			}
			tem_space++;
			strcpy(cmd_array[i],tem1_space);

			printf("%s\n",cmd_array[i]);
		}
		cmd_array[i] = (void *)0;

		int cmd_cmp =compare(cmd_array);

		if(cmd_cmp/10 == 1)
		{
			ret_val=execute_system_call(cmd_cmp,cmd_array);
		}
		else if(cmd_cmp/10 == 2)
		{
			{


				pid = fork();

				int wstatus;
				switch(pid)
				{
					case 0:
						//signal ignore
						signal(SIGINT,SIG_DFL);
						signal(SIGQUIT,SIG_DFL);
						signal(SIGTSTP,SIG_DFL);
						//signal ignore


						printf("child = %d\n",getpid());
						int n,i ,j,temp;
						pid_t ti;
						int buff[50];//array 
						int p[2];//read and write pid
						int h,oldin = 1,oldout = 0,oldout1;
						int count1 = 0;
						for(i=1;i<count+1;i++)
						{
							if(strcmp(cmd_array[i],"|")==0)
								count1++;
						}
						i=1;
						for(h = 0;h < count1+1;h++)
						{
							j = i; 
							if(h < count1)
							{
								while(strcmp(cmd_array[i++],"|") != 0);//searching '|' position 
								cmd_array[i-1] = NULL;//making argv null where we got '|' for using in execvp
							}

							if(pipe(p)==-1)//creating pipe pipe will write p[0]-read p[1]-write pid
							{

								perror("PIPE");
								exit(EXIT_FAILURE);
							}
							if(h == 1)
							{
								close(oldin);
								dup2(oldout,0);
							}
							if(h > 1)
							{
								close(oldin);
								dup2(oldout,0);

							}

							switch(ti=fork())//creating fork
							{
								case -1:
									perror("fork()");
									break;
								case 0:
									if(h < count1)
									{
										close(p[0]);
										dup2(p[1],1);
									}
									if(execvp(cmd_array[j],cmd_array+j) == -1)
									{
										perror("EXCVP");
									}  //replace child but read from pipe istead of stdin 
									break;
								default:
									waitpid(ti,0,0);

									;
							}
							//oldout1 = oldout;
							oldout = p[0];
							oldin = p[1];
							memset(p,0,8);

						}
						printf("child done");
						kill(getpid(),SIGKILL);
						break;
					case -1:
						perror("fork()");
						break;
					default:
						waitpid(pid,0,0);//waiting for child to exicute
						printf("parent\n");

						//	}
			}


		}
	}
	else if(cmd_cmp/10 == 3)
	{
		ret_val =execute_echo_fam(cmd_cmp,cmd_array);
	}
	else if(cmd_cmp/10 == 4)
	{
		print_list(head);
	}
	else if(cmd_cmp/10 == 5)
	{

		delete_at_last_fg(&head);

	}
	else if(cmd_cmp/10 == 6)
	{
		delete_at_last_bg(&head);
	}
	else if(cmd_cmp/10 == 7)
	{
	}
	else
	{
		printf("Not a proper command\n");
	}
	if(m == 1)
	{
		m = 0;
		insert_at_last(&head,cmd_array,count);


	}
	free(cmd_array);
	memset(cmd_buff,0,80);
}

}
