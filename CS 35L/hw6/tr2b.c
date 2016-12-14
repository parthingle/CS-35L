#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{

  if (argc != 3)
  {
    fprintf(stderr, "There need to be exactly 3 arguments!");
    exit(1);
  }
  
  char * a1 = argv[1];
  char * a2 = argv[2];

    // check whether two arguments have the same length
  int i = 0;

  if(strlen(a1)!=strlen(a2))
  {
    fprintf(stderr, "The arguments are not the same length!");
    exit(1);
  }

  if(!strlen(a1))
  {
    fprintf(stderr, "The arguments need to be atleast 1 character long!");
    exit(1);
  }

  char buffer;
  while((buffer = getchar()) != EOF)
  {
    int k = 0;
    while(a1[k] != '\0')
    {
      if(buffer == a1[k])
      {
	     break;
      }
      k++;
    }
    buffer = a2[k];
    putchar(buffer);
  }
  
  return 0;
}