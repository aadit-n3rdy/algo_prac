#include <stdio.h>
#include <string.h>

#define ASCII_A_LOWER_CASE 97
#define ASCII_A_UPPER_CASE 65
#define ASCII_Z_LOWER_CASE 122
#define ASCII_Z_UPPER_CASE 90


/* 
  Converts char to lower case if upper case
  Else returns char itself
*/
char toLowerCase(char chr) {
  if((int)chr >= ASCII_A_UPPER_CASE && (int)chr <= ASCII_Z_UPPER_CASE) {
    chr = (int)chr + 32;
  }
  return chr;
}

int checkStrUnique(char* str) {
  if(str==NULL) {
    return -2;
  }
  int i;
  int a;
  int bitmap=0;

  int length = strlen(str);
  for(i = 0; i < length; i++) {
    // If the character is present in the string,
    // a is the bit position in the bitmap which
    // will be set to 1
    char cur = toLowerCase(str[i]);
    if((int)cur > ASCII_Z_LOWER_CASE || (int)cur < ASCII_A_LOWER_CASE) {
      return -1;
    }
    a = 1<<((int)cur-ASCII_A_LOWER_CASE);
    // Check if bit position is already set, else
    // set it
    if(bitmap & a) {
      // Bit position was already set, char
      // exists in the string
      break;
    }
    else {
      // Set the bit position
      bitmap = bitmap | a;
    }
  }
  return i==length;
}

/* Assumptions:
  -> Input <= 99 chars
  -> Only lower case alphabets
*/
int main() {
  char inp[100];
  scanf("%100s", inp);
  int isUnique = checkStrUnique(0);
  if(isUnique == -1) {
    printf("ERROR: String has non-alphabet character");
  }
  else if(isUnique == -2) {
    printf("ERROR: NULL input");
  }
  else if(isUnique) {
    printf("String has unique chars");
  }
  else {
    printf("String does not have unique chars");
  }
}
