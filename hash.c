#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc, char* argv[])
{
  if(argc>2)
    {
      printf("Usage: ./hash [batch_file]");
      exit(1);
    }
  
  char* exitCmd = "exit\n";
  char *cmd = NULL;
  size_t bufLen = 0;  

  printf(">hash ");
  while(1)
    {
      getline(&cmd, &bufLen, stdin);
      
      if(strncmp(exitCmd, cmd, 5)==0)
	exit(0);

      int rc = fork();

      if(rc<0)
	{
	  fprintf(stderr, "Unable to create child process\n");
	  exit(1);
	}
      else if(rc==0)
	{
	  printf("In child\n");
	  printf("%s", cmd);
	  break;
	}
      else
	{
	  wait(NULL);
	  printf("In parent\n");
	  printf(">hash ");
	}
    }
}
