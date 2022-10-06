#include "common.h"

class Solution {
 public:
  vector<int> threeEqualParts(vector<int>& arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 3 != 0) return {-1, -1};
    if (sum == 0) return {0, 2};

    int partial   = sum / 3;
    sum           = 0;
    int leftCount = 0, midCount = 0, rightCount = 0;
    int leftLeft = -1, leftRight = 0, rightLeft = 0, rightRight = 0;
    for (int i = 0; i < arr.size(); ++i) {
      sum += arr[i];
      if (sum < partial) continue;
      if (rightLeft == -1 && leftLeft != 0) {
        rightLeft = i;
        ++i;
        while (arr[i] == 0) ++i;
        rightRight = i - 1;
        break;
      }
      if (leftLeft == 0) {
        leftLeft = i;
        ++i;
        while (arr[i] == 0) ++i;
        leftRight = i - 1;
        sum       = 0;
      }
    }
    int zeroCount = 0;
    while (arr[arr.size() - zeroCount - 1] == 0) ++zeroCount;

    if (leftRight - leftRight < zeroCount || rightRight - rightLeft < zeroCount)
      return {-1, -1};

    return {leftLeft + zeroCount, rightLeft + zeroCount};
  }
};

int main(int argc, char const* argv[]) {
  vector<int> arr = {1, 0, 1, 0, 1};

  Solution solution;

  auto result = solution.threeEqualParts(arr);
  print(result);

  return 0;
}
