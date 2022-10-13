#include "common.h"

class Solution {
 public:
  int maxChunksToSorted(vector<int>& arr) {
    int startMin    = 0;
    int currentMax  = 0;
    int bufferCount = 0;
    int chunksCount = 0;
    for (int i = 0; i < arr.size(); ++i) {
      if (arr[i] != startMin || currentMax < bufferCount) {
        currentMax = max(arr[i], currentMax);
        ++bufferCount;
        continue;
      }
      ++chunksCount;
      startMin += bufferCount;
      bufferCount = 0;
      currentMax  = max(arr[i], currentMax);
    }
    return chunksCount;
  }
};

int main(int argc, char const* argv[]) {
  Solution s;
  // auto     arr = load<vector<int>>("[1,4,3,6,0,7,8,2,5]");  // 1
  auto arr = load<vector<int>>("[1,0,2,3,4]");  // 4
  print(s.maxChunksToSorted(arr));

  return 0;
}
