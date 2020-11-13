#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*
 Struct for building strings, like a stringstream
*/
struct StringBuilder {
  char* data;
  int curBlocks;
};


/*
 Allocates 8 bytes of memory and initialised the
 StringBuilder
*/
int sbinit(struct StringBuilder* builder) {
  builder->data = (char*)calloc(8, sizeof(char));
  builder->curBlocks=1;
}

/*
 Returns the current capacity of the StringBuilder
 assuming no more reallocs
*/
int sbcapacity(struct StringBuilder* builder){
  return builder->curBlocks*8;
}

/*
 Returns the length of the string in the StringBuilder
 excluding the trailing null
*/
int sbsize(struct StringBuilder* builder) {
  int size=0;
  for(size=0; builder->data[size]!='\0'; size++){}
  return size;
}

/*
 Allocates 8 more bytes for the StringBuilder
*/
int sbexpand(struct StringBuilder* builder) {
   builder->curBlocks++;
   builder->data=realloc(builder->data, builder->curBlocks*sizeof(char)*8);
   for(int i=sbsize(builder); i < builder->curBlocks*8; i++) {
     builder->data[i] = '\0';
   }
}

int sbappendchar(struct StringBuilder* builder, char chr) {
  if(sbsize(builder)%8 <= 1) {
    sbexpand(builder);
  }
  builder->data[sbsize(builder)] = chr;
}

int sbappendstring(struct StringBuilder* builder, char* str) {
  int startSize = sbsize(builder);
  int i = 0;
  int len = strlen(str);
  for(int i = 0; i < len; i++) {
    if(i == sbcapacity(builder)-1) {
      sbexpand(builder);
    }
    builder->data[i+startSize] = str[i];
  }  
}


/*
 Copies the text in the builder into the string
 WARNING: MEMORY MUST BE ALLOCATED FOR str
 DOES NOT ALLOCATE MEMORY
*/
void sbget(struct StringBuilder* builder, char* str) {  
  int size = sbsize(builder);
  for(int i = 0; i < size; i++) {
    str[i] = builder->data[i];
  }
}

/*
 Replaces all the spaces in a string with 
 '%20' to make the string safe for HTML
*/
char* htmlSpace(char* str) {
  struct StringBuilder builder;
  sbinit(&builder);
  int length = strlen(str);
  for(int i = 0; i < strlen(str); i++) {
    // Appends %20 if the char is a space,
    // else appends the char itself
    if(str[i] == ' ') {
      sbappendstring(&builder, "%20");
    }
    else {
      sbappendchar(&builder, str[i]);
    }
  }
  char* output = calloc(sbsize(&builder), sizeof(char));
  sbget(&builder, output);
  return output;
}

int main() {
  char* input = calloc(20, sizeof(char));
  char* output;
  scanf("%[^\n]", input);
  output = htmlSpace(input);
  printf("The properly spaced string is:\n%s\n", output);
  return 0;
}
