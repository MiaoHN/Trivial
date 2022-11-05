#include "common.h"

class Solution {
 public:
  int maxRepeating(const string& sequence, const string& word) {
    if (word.size() > sequence.size()) return 0;

    int maxRepeat = 0;
    int repeat    = 0;
    int n         = sequence.size();

    for (int i = 0; i < n; ++i) {
      if (sequence[i] != word[0] || n - i < word.size()) {
        repeat = 0;
      } else {
        if (sequence.substr(i, word.size()) == word) {
          ++repeat;
          i += word.size() - 1;
        } else {
          repeat = 0;
        }
      }
      maxRepeat = max(maxRepeat, repeat);
    }

    return maxRepeat;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  string   sequence = "aaabaaaabaaabaaaabaaaabaaaabaaaaba";
  string   word     = "aaaba";
  int      result   = solution.maxRepeating(sequence, word);

  print(result);

  return 0;
}
