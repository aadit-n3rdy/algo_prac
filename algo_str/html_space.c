#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct StringBuilder {
  char* data;
  int curBlocks;
};

int sbinit(struct StringBuilder* builder) {
  builder->data = (char*)calloc(8, sizeof(char));
  builder->curBlocks=1;
}

int sbcapacity(struct StringBuilder* builder){
  return builder->curBlocks*8;
}

int sbsize(struct StringBuilder* builder) {
  int size=0;
  for(size=0; builder->data[size]!='\0'; size++){}
  return size+1;
}

int sbexpand(struct StringBuilder* builder) {
   builder->curBlocks++;
   builder->data=realloc(builder->data, builder->curBlocks*sizeof(char)*8);
   for(int i=sbsize(builder); i < builder->curBlocks*8; i++) {
     builder->data[i] = '\0';
   }
}

int sbappendchar(struct StringBuilder* builder, char chr) {
  if(sbsize(builder)%8 == 1) {
    sbexpand(builder);
  }
  builder->data[sbsize(builder)-1] = chr;
}

int sbappendstring(struct StringBuilder* builder, const char* str) {
  int startSize = sbsize(builder)-1;
  int i = 0;
  for(int i = 0; i < strlen(str); i++) {
    if(i == sbcapacity(builder)-1) {
      sbexpand(builder);
    }
    builder->data[i+startSize] = str[i];
  }
  
}

void sbget(struct StringBuilder* builder, char* str) {  
  int size = sbsize(builder);
  for(int i = 0; i < size-1; i++) {
    str[i] = builder->data[i];
  }	
}

int main() {
  char input[20];
  scanf("%[^\n]", input);
  struct StringBuilder builder;
  sbinit(&builder);
  int length = strlen(input);
  for(int i = 0; i < strlen(input); i++) {
    if(input[i] == ' ') {
      sbappendstring(&builder, "%20");
    }
    else {
      sbappendchar(&builder, input[i]);
    }
  }
  char* output=calloc(sbsize(&builder)+1, sizeof(char));
  sbget(&builder, output);
  printf("The properly spaced string is:\n%s\n", output);
  return 0;
}
