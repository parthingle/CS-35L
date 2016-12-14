#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
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

  char * tr1 = argv[1];
  char * tr2 = argv[2];

  // check whether two arguments have the same length
  if(strlen(tr1) != strlen(tr2))
  {
    fprintf(stderr, "Not the same size!");
    exit(1);
  }
  if(strlen(tr1)==0)
  {
    fprintf(stderr, "String cannot be empty!");
    exit(1);
  }


  char buffer;
  while(read(0, &buffer, 1) > 0)
  {
    int k = 0;
    while(tr1[k] != '\0')
    {
      if(buffer == tr1[k])
      {
       break;
      }
      k++;
    }
    buffer = tr2[k];
    int check=write(1, &buffer, 1);
    if(check<0)
    {
      fprintf(stderr, "Unrecognized write error!");
      exit(1);
    }
  }
  return 0;

}