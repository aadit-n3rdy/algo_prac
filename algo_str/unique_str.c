#include <stdio.h>
#include <string.h>

#define ASCII_A_LOWER_CASE 97
#define ASCII_A_UPPER_CASE 65
#define ASCII_Z_LOWER_CASE 122
#define ASCII_Z_UPPER_CASE 90

#define TEST_CASE_COUNT 4

struct TestData {
  const char* input;
  int output;
};

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

int checkStrUnique(const char* str) {
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

void test() {
  struct TestData testdata[TEST_CASE_COUNT];
  testdata[0].input = "abcde";
  testdata[0].output = 1;
  testdata[1].input = "abcda";
  testdata[1].output = 0;
  testdata[2].input = NULL;
  testdata[2].output = -2;
  testdata[3].input = "123abc";
  testdata[3].output = -1;

  for(int i = 0; i < TEST_CASE_COUNT; i++) {
    if(testdata[i].output != checkStrUnique(testdata[i].input)) {
      printf("Test %d FAILED\n", i);
    }
    else {
      printf("Test %d SUCCESS\n", i);
    }
  }
  return;
}

/* Assumptions:
  -> Input <= 99 chars
  -> Only lower case alphabets
*/
int main() {
  /*
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
  */
  test();
}


