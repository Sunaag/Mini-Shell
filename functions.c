#include "common.h"

int compare(char **cmd_buff)
{
	for(int i = 0; i < 3 ;i++)
	{
		if(strcmp(cmd_buff[1],ch_cmd.system_calls[i])==0)
		{
			return 10+i; 
		}
	}
	for(int i = 0; i < 4 ;i++)
	{
		if(strcmp(cmd_buff[1],ch_cmd.process[i])==0)
		{

			return 20+i; 
		}
	}
	if(strcmp(cmd_buff[1],"echo") == 0)
	{	
		for(int i = 0; i < 3 ;i++)
		{
			if(strcmp(cmd_buff[2],ch_cmd.echo_fam[i])==0)
			{
				return 30+i; 
			}
		}
	}
        if(strcmp(cmd_buff[1],"jobs") == 0)
        {
             if(cmd_buff[2]==NULL)
             {
                return 44;
             }
         }
    if(strcmp(cmd_buff[1],"fg") == 0)
        {
             if(cmd_buff[2]==NULL)
             {
                return 55;
             }
         }
    if(strcmp(cmd_buff[1],"bg") == 0)
        {
             if(cmd_buff[2]==NULL)
             {
                return 66;
             }
         }

	char *temp = cmd_buff[1];
	prompt_buff[0]='$';
	int i = 1;
	if(strncmp(cmd_buff[1],"PS1=",4)!=0)
	{
		while(*temp != '=' && *temp != '\0')
		{
			prompt_buff[i] = *temp++;
			i++;
		}
	}
	temp = cmd_buff[1];
	while(*temp != '=' && *temp != '\0')
	{
		temp++;
	}
	if(*temp == '=')
	{
		if(strcmp(temp+1,"$PS1") == 0)
		{
			strcpy(path_buff,buff);
		}
		else if(strncmp(cmd_buff[1],"PS1=",4) == 0)
		{
			if(strcmp(temp+1,prompt_buff)==0)
			{
				strcpy(buff,path_buff);
				memset(prompt_buff,0,80);
			}
			else
			{
				memset(buff,0,80);
				strcpy(buff,temp+1);
			}
		}
		return 77;
	}
	return 88;
}


int execute_system_call(int cmd_cmp,char **cmd_array)
{
	if(cmd_cmp % 10 == 0)
	{
		if(chdir(cmd_array[2]) == -1)
		{
			printf("No such directory\n");
		}
		else
		{
			memset(buff,0,80);
			getcwd(buff,80);
		}
	}
	else if(cmd_cmp % 10 == 1)
	{
		printf("%s\n",buff);
	}
	else
	{
		mkdir(cmd_array[2],0777);
	}
}

int execute_echo_fam(int cmd_cmp,char **cmd_array)
{
	if((cmd_cmp % 10) == 0)
	{
		printf("%d\n",getpid());
	}
	else if((cmd_cmp % 10) == 1)
	{
		printf("%d\n",ret_val);
	}
	else
	{
		printf("%s\n",shell_buff);
	}
	return 0;
}
