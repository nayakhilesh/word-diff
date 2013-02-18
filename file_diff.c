#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hash_table.h"

char* normalizestring(char *inputstring);
int hashfunction(char *input);
int eq(char *str1, char *str2);
void print(char *key, void* obj);
void addnode(char *str, void *obj);


typedef struct{
  char *string;
  void *next;
} node;

node *head = NULL;

int main (int argc, char **argv)
{

  FILE *file1, *file2;
  char buffer[1024];
  char *str, **str1;
  int m;
 
  /*
  for (m=0;m<argc;m++)
    {
      printf("argument %d: %s\n", m, argv[m]);
    }
  */
  
  if(argc != 3)
    {
      printf("please specify 2 input files\n");
      exit(1);
    }   

  file1 = fopen (argv[1], "r");
  file2 = fopen(argv[2],"r");

  if (!file1) {
    printf ("%s not found\n", argv[1]);
    exit (1);
  }

  if (!file2) {
    printf ("%s not found\n", argv[2]);
    exit (1);
  }

  hash_table_ptr hashtable = init_hash_table(hashfunction,eq,59);

  while(fgets(buffer, 1024, file1))
    {  
      str = strtok(buffer," \n\0");
      
      while(str)
	{
	  str1 = malloc(sizeof(char*));
	  *str1 = normalizestring(str);
	  if(strcmp(*str1,"\0"))
	    add(hashtable,*str1,NULL);
	  str = strtok(NULL," \n\0");
	  free(str1);
	}
    }
 
  //map(hashtable, print);
  
  while(fgets(buffer, 1024, file2))
    {  
      str = strtok(buffer," \n\0");
      
      while(str)
	{
	  str1 = malloc(sizeof(char*));
	  *str1 = normalizestring(str);
	  if(strcmp(*str1,"\0"))
	    delete(hashtable,*str1,1);
	  str = strtok(NULL," \n\0");
	  free(*str1);
	  free(str1);
	}
    }
  
  //map(hashtable, print);

  map(hashtable, addnode);

  node *index = head;

  while(index)
    {
      printf("%s\n", index->string);
      index = index->next;
    }

  fclose(file1);
  fclose(file2);

}

char* normalizestring(char *inputstring)
{
  char *pointer = malloc((strlen(inputstring)+1)*sizeof(char));
  int i=0, j=0;

  while(inputstring[j])
    {
      if (isalpha(inputstring[j]))
	{
	  pointer[i] = toupper(inputstring[j]);
	  i++;
	}
      j++;	 
    }

  pointer[i] = '\0';

  return pointer;
}

int hashfunction(char *input)
{
  int i = 0;
  unsigned short int value = 0;
  while (input[i])
    {
      value += ((unsigned short int)(input[i]));
      i++;
    }

  return (value % 59);

}

int eq(char *str1, char *str2)
{
  return (strcmp(str1,str2) == 0);
}

void print(char *key, void* obj)
{
  printf ("table value: %s ", key);
  printf("%d\n", hashfunction(key));
}


void addnode(char *str, void *obj)
{
  node *ptr = malloc(sizeof(node));   

  ptr->string = str;
  ptr->next = NULL;
  
  node *current, *prev;
  prev = current = head;

  if(head == NULL)
    {
      head = ptr;
      return;
    }

  while(current)
    {
      if(strcmp(ptr->string,current->string)<0)
	{
	  if(prev == current)
	    {
	      head = ptr;
	      ptr->next  = current;
	    }
	  else
	    {
	      prev->next = ptr;
	      ptr->next = current;
	    }
	  return;
	}
      prev = current;
      current = current->next;
    }

  prev->next = ptr;   
} 

