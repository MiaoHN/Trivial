#include "common.h"

class Solution {
 public:
  // 1. 分片
  // 2. 判断合法性
  // 3. 添加
  vector<string> ambiguousCoordinates(string const& s) {
    vector<string> result;
    int            n = s.size();

    for (int i = 1; i < n - 2; ++i) {
      string first  = s.substr(1, i);
      string second = s.substr(i + 1, n - i - 2);
      if (first[0] == '0') {
        first.insert(1, ".");
        if (second[0] == '0') {
          second.insert(1, ".");
          result.push_back("(" + first + ", " + second + ")");
          continue;
        } else {
          for (int i = 1; i < second.size() - 1; ++i) {
            string tmp = second;
            tmp.insert(i, ".");
            result.push_back("(" + first + ", " + tmp + ")");
          }
        }
      } else {
        for (int i = 1; i < first.size() - 1; ++i) {
          string tmp = first;
          tmp.insert(i, ".");

          if (second[0] == '0') {
            second.insert(1, ".");
            result.push_back("(" + tmp + ", " + second + ")");
            continue;
          } else {
            for (int i = 1; i < second.size() - 1; ++i) {
              string tmp1 = second;
              tmp1.insert(i, ".");
              result.push_back("(" + tmp + ", " + tmp1 + ")");
            }
          }
        }
      }
    }

    return result;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  string   s = "(123)";
  print(solution.ambiguousCoordinates(s));
  return 0;
}
