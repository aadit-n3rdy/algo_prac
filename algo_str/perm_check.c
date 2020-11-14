#include <stdio.h>
#include <string.h>

#define ASCII_A_LOWER_CASE 97
#define ASCII_A_UPPER_CASE 65
#define ASCII_Z_LOWER_CASE 122
#define ASCII_Z_UPPER_CASE 90

/*
 Converts char to lower case if upper case
 Else returns char itsel
*/
char toLowerCase(char chr) {
  if((int)char >= ASCII_A_UPPER_CASE && (int)char <= ASCII_Z_UPPER_CASE) {
    chr = (int)chr + 32;
  }
  return chr;
}

int checkPermutation(const char* str1, const char* str2) {
  if( str1 == NULL || str2 == NULL) {
    return -2;
  }
  int bitmap = 0;
  int l1 = strlen(str1);
  int l2 = strlen(str2);
  for(int i = 0; i < l1; i++) {
    char cur = toLowerCase(str[i]);
    if((int)cur > ASCII_Z_LOWER_CASE || (int)cur < ASCII_A_LOWER_CASE) {
      return -1;
    }
    int bit = 1<<((int)cur - ASCII_A_LOWER_CASE);
    bitmap = bitmap | bit;
  }
  int i = 0;
  for(i = 0; i < l2; i++) {
    char cur = toLowerCase(str2[i]);
    if((int)cur > ASCII_Z_LOWER_CASE || (int)cur < ASCII_A_LOWER_CASE) {
      return -1;
    }
    int bit = 1<<((int)cur - ASCII_A_LOWER_CASE);
    if(!(bitmap & bit)) {
      break;
    }
  }
  return !(i==l2);
}
