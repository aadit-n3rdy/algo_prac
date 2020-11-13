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
  while(str[i] != '\0') {
    if(i==sbcapacity(builder)-1) {
      sbexpand(builder);
    }
    builder->data[i+startSize] = str[i];
  }
}

void sbget(struct StringBuilder* builder, char** pString) {  
  int size = sbsize(builder);
  *pString = (char*)calloc(size, sizeof(char));
  for(int i = 0; i < size-1; i++) {
    *pString[i] = builder->data[i];
  }	
}

int cust_strlen(char* str) {
  int size=0;
  for(size=0; str != '\0'; str++, size++){
    printf("Calcing length");
  }
  return size;
}

int main() {
  char input[20];
  printf("Getting input: \n");
  scanf("%s"
  printf("Input done\n");
  struct StringBuilder builder;
  sbinit(&builder);
  int length = cust_strlen(input);
  printf("%d\n", length);
  for(int i = 0; i < length;  input++, i++) {
    printf("In the loop\n");
    if(input == ' ') {
      printf("Pusing space at index %d\n", i);
      sbappendstring(&builder, "%20\0");
    }
    else {
      sbappendchar(&builder, *input);
    }
  }
  printf("Loop done\n");
  char* output;
  sbget(&builder, &output);
  printf("The properly spaced string is:\n%s", output);
  return 0;
}
