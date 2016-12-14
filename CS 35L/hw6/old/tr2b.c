#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
  //Check for correct number of args
  
  if (argc > 3)
  {
   fprintf(stderr, "Error: more than 2 arguments");
   exit(1);
  }

  if (argc == 1)
  {
    fprintf(stderr, "Error: no argument");
    exit(1);
  }

  if (argc == 2)
  {
    fprintf(stderr, "Error: need one more argument");
    exit(1);
  }

  char* from = argv[1];
  char* to = argv[2];
  //Make sure they are of the same length


  if(strlen(from) != strlen(to))
  {
    fprintf(stderr, "Not the same size!");
    exit(1);
  }

  if(strlen(from)==0)
  {
    fprintf(stderr, "The string cannot be empty!");
    exit(1);
  }

  //Make sure FROM does not contain any duplicate bytes
  for(size_t i = 0; i < strlen(from); i++)
  {
    for(size_t j = i+1; j < strlen(from); j++)
    {
      if(from[j] == from[i])
      {
        fprintf(stderr, "From should not contain duplicate bytes!");
        exit(1);
      }
    }
  }

  char curr = getchar();
  int matchInFrom = 0;

  while(curr != EOF)
  {
    for(size_t i = 0; i < strlen(from); i++)
    {
      if(curr == from[i])
      {
      
      matchInFrom = 1;
      break;
      }
      else
      {
        matchInFrom = 0;
      }
    
    if(matchInFrom==0)
    {
     putchar(curr);
    }
    else
    {
      putchar(to[i]);
    }
    curr = getchar();
    }
  }

    return 0;
}

