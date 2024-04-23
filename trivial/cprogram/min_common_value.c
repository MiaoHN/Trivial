#include <stdio.h>
#define INT_MAX 1000000

int main(int argc, char const* argv[]) {
  int n1, n2;
  int arr1[50], arr2[50];

  scanf("%d %d", &n1, &n2);
  for (int i = 0; i < n1; i++) {
    scanf("%d", &arr1[i]);
  }
  for (int i = 0; i < n2; i++) {
    scanf("%d", &arr2[i]);
  }

  int* ptr1 = arr1;
  int* ptr2 = arr2;

  int min = INT_MAX;

  while (ptr1 < arr1 + n1) {
    while (ptr2 < arr2 + n2) {
      if (*ptr1 == *ptr2) {
        if (*ptr1 < min) {
          min = *ptr1;
        }
      }
      ptr2++;
    }
    ptr2 = arr2;
    ptr1++;
  }

  if (min == INT_MAX) {
    printf("-1\n");
  } else {
    printf("%d\n", min);
  }

  return 0;
}
