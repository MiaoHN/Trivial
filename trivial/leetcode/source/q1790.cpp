#include "common.h"

class Solution {
 public:
  bool areAlmostEqual(string s1, string s2) {
    if (s1.size() != s2.size()) return false;
    int n     = s1.size();
    int count = 0;
    int sum   = 0;
    for (int i = 0; i < n; ++i) {
      int diff = s1[i] - s2[i];
      if (diff != 0) {
        sum += diff;
        ++count;
      }
      if (count == 3) return false;
    }
    return sum == 0;
  }
};

int main(int argc, char const *argv[]) {
  Solution solution;
  string   s1 = "bf";
  string   s2 = "dd";
  print(solution.areAlmostEqual(s1, s2));
  return 0;
}
