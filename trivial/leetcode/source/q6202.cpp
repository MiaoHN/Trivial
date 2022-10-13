#include "common.h"

class Solution {
 public:
  vector<int> robot(const vector<int>& indices) {
    int         cursor = 1;
    vector<int> result;
    result.push_back(indices[0]);
    while (cursor < indices.size()) {
      if (indices[cursor] > indices[cursor - 1]) {
        result.push_back(indices[cursor]);
        ++cursor;
      } else {
        int right = cursor + 1;
        while (right < indices.size() && indices[right] < indices[cursor - 1])
          ++right;
        for (int i = right - 1; i >= cursor; --i) {
          result.push_back(indices[i]);
        }
        cursor = right;
        if (cursor < indices.size()) {
          result.push_back(indices[cursor++]);
        }
      }
    }
    return result;
  }

  string robotWithString(string s) {
    vector<int> indices(s.size());
    iota(indices.begin(), indices.end(), 0);
    sort(indices.begin(), indices.end(),
         [s](int a, int b) { return s[a] < s[b]; });
    string result;

    vector<int> idx = robot(indices);
    for (auto i : idx) {
      result.push_back(s[i]);
    }

    return result;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  print(solution.robotWithString("bydizfve"));
  return 0;
}
