#include "common.h"

/*
76 - 最小覆盖字串

https://leetcode.cn/problems/minimum-window-substring


*/

class Solution {
 public:
  string minWindow(string s, string t) {
    vector<int> indices;
    string      result = "";
    sort(t.begin(), t.end());
    for (int i = 0; i < s.size(); ++i) {
      auto iter = find(t.begin(), t.end(), s[i]);
      if (iter != t.end()) {
        indices.push_back(i);
      }
    }

    for (int left = 0; left < indices.size() - t.size() + 1; ++left) {
      string tmp;
      for (int i = left; i < left + t.size(); ++i) {
        tmp += s[indices[i]];
      }
      sort(tmp.begin(), tmp.end());
      if (tmp == t) {
        string str = s.substr(indices[left],
                              indices[t.size() + left - 1] - indices[left] + 1);
        if (result == "" || result.size() > str.size()) {
          result = str;
        }
      }
    }
    return result;
  }
};

int main(int argc, char const *argv[]) {
  string   s = "aaaaaaaaaaaabbbbbcdd";
  string   t = "abcdd";
  Solution solution;
  print(solution.minWindow(s, t));
  return 0;
}
