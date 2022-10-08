#include "common.h"

// leetcode 870 - 优势洗牌
// url: https://leetcode.cn/problems/advantage-shuffle/
//
// 思路：田忌赛马

class Solution {
 public:
  vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
    int         n = nums1.size(), ids[n];
    vector<int> ans(n);
    sort(nums1.begin(), nums1.end());
    iota(ids, ids + n, 0);
    sort(ids, ids + n, [&](int i, int j) { return nums2[i] < nums2[j]; });
    int left = 0, right = n - 1;
    for (const auto& x : nums1) {
      ans[x > nums2[ids[left]] ? ids[left++] : ids[right--]] = x;
    }
    return ans;
  }
};

int main(int argc, char const* argv[]) {
  auto     vec1 = load<vector<int>>("[12,24,8,32]");
  auto     vec2 = load<vector<int>>("[13,25,32,11]");
  Solution solution;
  auto     result = solution.advantageCount(vec1, vec2);
  print(result);
  return 0;
}
