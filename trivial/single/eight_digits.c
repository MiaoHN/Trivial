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

/**
 * @brief 解决八数码问题
 *
 * @param start 初始状态
 * @param end 目标状态
 * @return int 最小步数，无解返回 -1
 */
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

int eight_digits(char *start, char *end) {
  int max_depth = 100;
  int depth = 0;
  char queue[MAXN][10];

  int head = 0;
  int tail = 0;

  int visited[MAXN] = {0};

  int step[MAXN] = {0};

  int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  strcpy(queue[tail], start);

  tail++;
  visited[head] = 1;

  while (head < tail) {
    if (depth > max_depth) {
      return -1;
    }
    char *current = queue[head];

    if (strcmp(current, end) == 0) {
      return step[head];
    }

    int zero_index = 0;
    for (int i = 0; i < 9; i++) {
      if (current[i] == '0') {
        zero_index = i;
        break;
      }
    }

    int x = zero_index / 3;
    int y = zero_index % 3;

    for (int i = 0; i < 4; i++) {
      int new_x = x + direction[i][0];
      int new_y = y + direction[i][1];

      if (new_x >= 0 && new_x < 3 && new_y >= 0 && new_y < 3) {
        char new_state[10];
        strcpy(new_state, current);

        int new_zero_index = new_x * 3 + new_y;

        new_state[zero_index] = new_state[new_zero_index];
        new_state[new_zero_index] = '0';

        int found = 0;
        for (int j = 0; j < tail; j++) {
          if (strcmp(queue[j], new_state) == 0) {
            found = 1;
            break;
          }
        }

        if (!found) {
          strcpy(queue[tail], new_state);
          tail++;
          visited[tail] = 1;
          step[tail] = step[head] + 1;
        }
      }
    }

    head++;
    depth++;
  }

  return -1;
}
