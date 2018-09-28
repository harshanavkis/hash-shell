#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
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

  while(1)
    {
      printf(">hash ");

      getline(&cmd, &bufLen, stdin);
            
      if(strncmp(exitCmd, cmd, 5)==0)
	exit(0);
      printf("%s", cmd);      
    }
}
