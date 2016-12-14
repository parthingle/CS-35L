
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
//#include <sys/types.h>

//global variable
int cmp_count = 0;


int frobcmp(char const * a, char const * b)
{
  //increment this count every time frobcmp gets called
  cmp_count++;
  
  //iterate through both arrays
  while ((*a != 32) && (*b != 32))
    {
      if ((*a^42) > (*b^42))
	{
	  return 1;
	}
      else if ((*a^42) < (*b^42))
	{
	  return -1;
	}
      a++;
      b++;
    }

  //if the program executes to this point
  //it means that either one frobnicated word might
  //be a prefix of another or both are equal

  //a is a prefix of b
  if ((*a == 32) && (*b != 32))
    {
      return -1;
    }
  //b is a prefix of a
  else if ((*a != 32) && (*b == 32))
    {
      return 1;
    }

  //both are equal
  return 0;
}

int wrap_frobcmp(const void * a, const void * b)
{
  char const * firstw = *(char const **)a;
  char const * secondw = *(char const **)b;
  return frobcmp(firstw, secondw);
}

int main()
{

  int char_in;
  struct stat fileINFO;
  fstat(0, &fileINFO);
  int size_file = fileINFO.st_size;
  int countWord = 0;
  int i = 0;
  char * char_input_array;
  
  if(!S_ISREG(fileINFO.st_mode))
  {
    if(read(0, &char_in, 1) == 0){
      fprintf(stderr, "Comparisons: %d\n", 0);
      return 0;
    }

    //pre-allocate a chunk of memory
    int pre_allocate = 1024;
    char_input_array = (char*)malloc(sizeof(char)*pre_allocate);
  
    //report error when memory allocation fails
    if (char_input_array == NULL){
      fprintf(stderr,"Array of chars: memory allocation failed.");
      exit(1);
    }

    //int char_in;
    //int countWord=0;

    char_input_array[i] = char_in;
    i++;
    
    while(read(0, &char_in, 1) > 0)
    {
      //reach the end of the memory chunk, need to reallocate memory
      if(i == pre_allocate)
	{
	  char_input_array = (char*)realloc(char_input_array, pre_allocate*2);

	  //report error when memory reallocation fails
	  if (char_input_array ==NULL)
	    {
	      fprintf(stderr, "Memory reallocation failed.");
	      exit(1);
	    }

	  //update allocation size
	  pre_allocate *=2;
	}
    
      
      //count how many words seperated by space in the array
      if((char)char_in == ' ')
	{
	  countWord++;
	}
	

      //avoid adding a newline at the end of input
      if((char)char_in == '\n')
	{
	  countWord++;
	  char_input_array[i] = ' ';
	  continue;
	}
      
      //store char into the array
      char_input_array[i]=(char)char_in;
      i++;
    }
  }

  else if (S_ISREG(fileINFO.st_mode)){

    if(read(0, &char_in, 1) == 0){
      fprintf(stderr, "Comparisons: %d\n", 0);
      return 0;
    }

    //pre-allocate a chunk of memory to store the entire file
    char_input_array = (char*)malloc(sizeof(char)*size_file);

    //report error when memory allocation fails
    if (char_input_array == NULL){
      fprintf(stderr,"Array of chars: memory allocation failed.");
      exit(1);
    }

    char_input_array[i] = char_in;
    i++;
    int size_allocate = size_file;
    int p;
    
    while(read(0, &char_in, 1)>0)
    {
      //reach the end of the memory chunk, need to reallocate memory
      if(i == size_allocate)
	{
	  char_input_array = (char*)realloc(char_input_array, size_allocate*2);

	  //report error when memory reallocation fails
	  if (char_input_array ==NULL)
	    {
	      fprintf(stderr, "Memory reallocation failed.");
	      exit(1);
	    }

	  //update allocation size
	  size_allocate *=2;
	}
    
      
      //count how many words seperated by space in the array
      if((char)char_in == ' ')
	{
	  countWord++;
	}
	

      //avoid adding a newline at the end of input
      if((char)char_in == '\n')
	{
	  countWord++;
	  char_input_array[i] = ' ';
	  i++;
	  continue;
	}

      
      //store char into the array
      char_input_array[i]=(char)char_in;
      i++;

      //check whether the file is growing and update the new size
      p++;
      fstat(0, &fileINFO);
      size_file = fileINFO.st_size;
    } 
  }

  /*
    
  //standard input ends with nonspace
  if(char_input_array[i] != ' ')
    {
      countWord++;

      //append a trailing space at the end of the array
      char_input_array[i] = ' ';
    }
  */
  
  //count size of the array
  int arraySize = i;
  
  //error flag is set during input
  if (ferror(stdin))
    {
      fprintf(stderr,"An error occured while reading from stdin.");
      exit(1);
    }

  //create an array of pointers pointing to frobnicated words
  char ** ptrToWord = (char**)malloc(sizeof(char*)*countWord);

  if (ptrToWord == NULL)
    {
      fprintf(stderr, "Array of char pointers: memory allocation failed.");
      exit(1);
    }

  int k;

  //create a pointer pointing to the beginning of the char array
  char * voyager = char_input_array; 

  for (k=0; k < countWord; ++k)
    {
      ptrToWord[k] = voyager;

      //reach the end of the array of char pointers
      if (k == (countWord -1))
	{
	  break;
	}
       
      //voyager keep moving forward till next space
      while(*voyager != ' ')
	{
	  voyager++;
	}
      
      voyager++;
    }


  //sort char pointers
  qsort(ptrToWord, countWord, sizeof(char*), wrap_frobcmp);

  //output sorted frobnicated words
  int m;
  char * extractor;
  for (m=0; m < countWord; ++m)
    {
      extractor = ptrToWord[m];

      write(1, &(*extractor), 1);

      //extractor keep moving forward till the end of the word
      while (*extractor != ' ')
	{
	  extractor++;
	  write(1, &(*extractor), 1);
	}
    }

  /*
  //error flag is set during output
  if (ferror(stdout))
    {
      fprintf(stderr, "write failed\n");
    }
  */
  
  free(char_input_array);
  free(ptrToWord);
  fprintf (stderr, "Comparisons: %d\n", cmp_count);
  return 0;
}