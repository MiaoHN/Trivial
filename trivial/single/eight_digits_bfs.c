/*
八数码问题

样例输入：
283164705
123804765

样例输出：
14
*/

#include <stdio.h>
#include <string.h>

#define MAXN 10000

int eight_digits(char *start, char *end);

int main(int argc, char const *argv[]) {
  char start[10];
  char target[10];
  scanf("%s", start);
  scanf("%s", target);

  int result = eight_digits(start, target);

  printf("%d\n", result);

  return 0;
}

int eight_digits_bfs(char *start, char *end, int depth, int max_depth) {
  if (depth > max_depth) {
    return -1;
  }

  int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  char new_state[10];
  for (int i = 0; i < 4; ++i) {
    int x = 0;
    int y = 0;
    for (int j = 0; j < 9; ++j) {
      if (start[j] == '0') {
        x = j / 3;
        y = j % 3;
        break;
      }
    }
    int new_x = x + direction[i][0];
    int new_y = y + direction[i][1];
    if (new_x >= 0 && new_x < 3 && new_y >= 0 && new_y < 3) {
      strcpy(new_state, start);
      new_state[x * 3 + y] = new_state[new_x * 3 + new_y];
      new_state[new_x * 3 + new_y] = '0';
      if (strcmp(new_state, end) == 0) {
        return depth + 1;
      }
      int result = eight_digits_bfs(new_state, end, depth + 1, max_depth);
      if (result != -1) {
        return result;
      }
    }
  }

  return -1;
}

int eight_digits(char *start, char *end) {
  return eight_digits_bfs(start, end, 0, 500);
}
