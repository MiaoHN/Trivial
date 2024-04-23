/**
 * Reverse the words in a string using pointer
 *
 * Example:
 *  Input: "Hello World"
 *  Output: "World Hello"
 */
#include <stdio.h>
#include <string.h>

void simplify(char* str) {
  char* p1 = str;
  char* p2 = str;
  int n = 0;

  while (*p2) {
    if (*p2 == ' ' && (n == 0 || *(p2 + 1) == ' ' || *(p2 + 1) == '\0')) {
      p2++;
    } else {
      *p1 = *p2;
      p1++;
      p2++;
      n++;
    }
  }

  *p1 = '\0';
}

void reverse(char* start, char* end) {
  char temp;
  while (start < end) {
    temp = *start;
    *start = *end;
    *end = temp;
    start++;
    end--;
  }
}

int main(int argc, char const* argv[]) {
  char str[100];
  scanf("%[^\n]", str);

  simplify(str);

  reverse(str, str + strlen(str) - 1);

  char* start = str;
  char* end = str;

  while (*end) {
    if (*(end + 1) == '\0') {
      reverse(start, end);
    } else if (*end == ' ') {
      reverse(start, end - 1);
      while (*(end + 1) && *(end + 1) == ' ') {
        end++;
      }
      start = end + 1;
    }
    end++;
  }

  printf("%s\n", str);

  return 0;
}
