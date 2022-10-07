#include "common.h"

class Solution {
 public:
  int maxAscendingSum(vector<int>& nums) {
    int result = 0, total = nums[0];
    for (int cursor = 1; cursor < nums.size(); ++cursor) {
      total += nums[cursor];
      result = max(result, total);
      if (nums[cursor - 1] >= nums[cursor]) total = nums[cursor];
    }
    result = max(result, total);
    return result;
  }
};

int main(int argc, char const* argv[]) {
  vector<int> nums = {10, 20, 30, 5, 10, 50};
  Solution    so;
  print(so.maxAscendingSum(nums));
  return 0;
}
