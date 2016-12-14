#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

 
char defrob(const char ch)
{ 
  return (char)ch^42; 
} 

 
void defrobword(char *ch)
{ 
   for (int i = 0; ch[i]!=' '; ++i)
   { 
     ch[i]=defrob(ch[i]); 
   } 
} 
 
 
int frobcmp(const void *ca, const void *cb)
{ 
  char *a1 = *(char **)ca; 
  char *b1 = *(char **)cb; 
  char aa[300], bb[300]; 
  for(int i=0; a1[i]!=' '; i++)
  { 
  aa[i]=defrob(a1[i]); 
  } 
  
   for(int i=0; b1[i]!=' '; i++)
   { 
     bb[i]=defrob(b1[i]); 
   } 
   int k=0; 
   while(aa[k]!=' ' && bb[k]!=' ')
   { 
     if(aa[k]<bb[k])return -1; 
     if(bb[k]<aa[k])return 1; 
     k++; 
   } 
   if(aa[k]==bb[k])
    {
        return 0; 
    }
   if(aa[k]==' ')
   {
       return -1; 
   }
   return 1; 
} 
 
 
int main()
{ 
  int n_cols = 400; 
  int ct = 0; 
  char *arr; 
  arr= (char*)malloc(sizeof(char) * n_cols); 
  if (arr==NULL)
  { 
    fprintf(stderr, "Could not allocate memory."); 
    exit(1); 
  } 
  char ch='#'; 
  int i=0; 
  int words=0; 
  while(ch!=EOF)
  { 
    if(i==n_cols)
  { 
   arr=realloc(arr, sizeof(char)*n_cols*2); 
   n_cols=n_cols*2; 
   if (arr==NULL)
   { 
 	fprintf(stderr, "Could not re-allocate memory."); 
 	exit(1); 
   } 
  } 
    ch=getchar(); 
    if (ch!=EOF)
    { 
       arr[i]=ch; 
       i=i+1; 
    } 
    if(ch==' ')
    {
        words++; 
    }
   } 
   if(arr[i-1]!=' ')
   { 
     arr[i++]=' '; 
     words++; 
   } 
   char **p; 
   p=(char**)malloc(sizeof(char*) * (words)); 
   if(p==NULL)
   { 
     fprintf(stderr, "Could not allocate memory."); 
     exit(1); 
   } 
   int k=0; 
   p[k]=arr; 
   for (int j = 0; j<(i); ++j)
   { 
     if(arr[j]==' ')
     { 
       k++; 
       if(j<(i-1))p[k]=&arr[j+1]; 
     } 
   } 
   qsort(p, k, sizeof(char*), frobcmp); 
   for(int j=0; j<k; ++j)
   { 
     for(int d=0; p[j][d]!=' '; d++)
     { 
       putchar(p[j][d]); 
     } 
     putchar(' '); 
   } 
   free(arr); 
   free(p); 
} 
