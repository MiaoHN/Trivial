#include "common.h"

class Solution {
 public:
  int secondHighest(string s) {
    unordered_map<int, int> record;
    for (auto& c : s) {
      if (isdigit(c)) record[c - '0']++;
    }
    if (record.size() <= 1) return -1;
    bool meet_largest = false;
    for (int i = 9; i >= 0; --i) {
      if (record.count(i) > 0) {
        if (!meet_largest) {
          meet_largest = true;
        } else {
          return i;
        }
      }
    }
    return -1;
  }
};

int main(int argc, char** argv) {
  Solution solution;
  string s = "dfa12321afd";
  print(solution.secondHighest(s));
  return 0;
}
