#include <stdio.h>
#include <memory.h>
#include <ctype.h>

#define MAX_LENGTH 81

// This functin is used to trim the new line out of a string
void trimNewLineChar(char* str);

/* This function is used to check whether the user input is valid
 * if it is valid, we return 1 represents insert command, 2 represents
 * delete command, 3 represents quit command.
 * if it is invalid, we return 0
 * we will empty the input buffer in this function
 */
int getUserChoice();

// This function is used to do insert command
void insert(char* str);

// This function is used to do delete command
void delete(char* str);

int main() {
  printf("Enter the source string:\n");
  char srcString[MAX_LENGTH];
  fgets(srcString, MAX_LENGTH, stdin); // get the source string
  trimNewLineChar(srcString); // trim the new line

  printf("Source string is: \'%s\'\n", srcString);

  int choice = 0;
  do{
    printf("Enter [Dd] (delete), [Ii] (insert) or [Qq] (quit):\n");
    choice = getUserChoice(); // check whether user's choice is valid
    switch(choice) {
      case 1: insert(srcString); break;
      case 2: delete(srcString); break;
      case 3: break; // if user choice to quit, we do nothing
      default: printf("Invalid command\n"); // no need to break in default case
    }
    if(choice != 3)
      printf("Source string is: \'%s\'\n", srcString);
  }while(choice != 3);

  printf("Final string: \'%s\'\n", srcString);
  return 0;
}

void trimNewLineChar(char* str) {
  int size = strlen(str);
  if(str[size - 1] == '\n') // check whether the last character is new line
    str[size - 1] = '\0';
}

int getUserChoice() {
  char userChoice, otherChar;
  scanf(" %c", &userChoice); // get the first char in the input buffer

  // empty the input buffer
  do {
    otherChar = getchar();
  } while(otherChar != '\n');

  userChoice = tolower(userChoice);
  switch (userChoice) {
    case 'i': return 1;
    case 'd': return 2;
    case 'q': return 3;
    default: return 0;
  }
}

void insert(char* str) {
  char insertString[MAX_LENGTH];
  printf("Enter string to insert:\n");
  fgets(insertString, MAX_LENGTH, stdin);
  trimNewLineChar(insertString);

  int insertPostion = 0;
  printf("Enter position to insert:\n");
  scanf(" %d", &insertPostion);
  // TO DO; We need to judge whether this position is out of range
  // empty the buffer

  char destString[MAX_LENGTH];
  memset(destString, '\0', MAX_LENGTH);
  strncpy(destString, str, insertPostion);
  strcat(destString, insertString);
  strcat(destString, &str[insertPostion]);
  strcpy(str, destString);
}

void delete(char* str) {
  char deletedString[MAX_LENGTH];
  printf("Enter string to delete:\n");
  fgets(deletedString, MAX_LENGTH, stdin);
  trimNewLineChar(deletedString);

  char* deletePos = strstr(str, deletedString);

  // if we did find the substring, we return back to the main function
  if(deletePos == NULL) {
    printf("Error, \'%s\' not found\n", deletedString);
    return;
  }

  size_t deletePosition = deletePos - str;
  size_t deleteStrSize = strlen(deletedString);

  char destString[MAX_LENGTH];
  memset(destString, '\0', MAX_LENGTH);
  strncpy(destString, str, deletePosition);
  strcat(destString, str + deletePosition + deleteStrSize);
  strcpy(str, destString);
}





