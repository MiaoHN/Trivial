#include "common.h"

class Solution {
 public:
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 1; ++i) {
      if (nums[i] == nums[i + 1]) continue;
      for (int j = i + 1; j < nums.size() - 1; ++j) {
        if (nums[j] == nums[j + 1]) continue;
        int partial = target - nums[i] - nums[j];
        int p1 = j + 1, p2 = nums.size() - 1;
        while (p1 < nums.size() - 1 && nums[p1] == nums[p1 + 1]) {
          ++p1;
        }
        while (p2 > p1 && nums[p2] == nums[p2 - 1]) {
          --p2;
        }
        while (p1 < p2) {
          int sum = nums[p1] + nums[p2];
          if (sum == partial) {
            result.push_back({nums[i], nums[j], nums[p1], nums[p2]});
            ++p1;
          }
          if (sum < partial) ++p1;
          if (sum > partial) --p2;
        }
      }
    }
    return result;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<int> nums = {1, 0, -1, 0, -2, 2};
  int target = 0;
  auto result = solution.fourSum(nums, target);

  print(result);

  return 0;
}
