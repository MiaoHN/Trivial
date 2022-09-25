#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int temperatureTrend(vector<int> &temperatureA, vector<int> &temperatureB) {
    vector<int> da, db;
    // abcdefghijklmnopqrstuvwxyz
    // !@$%^&*()_+=\|][;:'"/.`~,"]
    int n = temperatureA.size();
    for (int i = 0; i < n - 1; ++i) {
      if (temperatureA[i] > temperatureA[i + 1]) {
        da.push_back(-1);
      } else if (temperatureA[i] == temperatureA[i + 1]) {
        da.push_back(0);
      } else {
        da.push_back(1);
      }
      if (temperatureB[i] > temperatureB[i + 1]) {
        db.push_back(-1);
      } else if (temperatureB[i] == temperatureB[i + 1]) {
        db.push_back(0);
      } else {
        db.push_back(1);
      }
    }
    int len    = 0;
    int maxLen = 0;
    for (int i = 0; i < da.size(); ++i) {
      if (da[i] == db[i]) {
        ++len;
        maxLen = max(len, maxLen);
      } else
        len = 0;
    }

    return maxLen;
  }
};

int main(int argc, char **argv) {
  Solution    solution;
  vector<int> a = {21, 18, 18, 18, 31};
  vector<int> b = {34, 32, 16, 16, 17};
  cout << solution.temperatureTrend(a, b) << endl;
  a = {-14, 7, -19, 9, 13, 40, 19, 15, -18};
  b = {3, 16, 28, 32, 25, 12, 13, -6, 4};
  cout << solution.temperatureTrend(a, b) << endl;
  return 0;
}