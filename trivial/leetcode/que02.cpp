#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int transportationHub(vector<vector<int>> &path) {
    unordered_map<int, set<int>> outGraph;
    unordered_map<int, set<int>> inGraph;
    for (auto &line : path) {
      if (inGraph.find(line[0]) == inGraph.end()) {
        inGraph[line[0]] = set<int>();
      }
      if (inGraph.find(line[1]) == inGraph.end()) {
        inGraph[line[1]] = set<int>();
      }
      if (outGraph.find(line[1]) == outGraph.end()) {
        outGraph[line[1]] = set<int>();
      }
      if (outGraph.find(line[0]) == outGraph.end()) {
        outGraph[line[0]] = set<int>();
      }
      outGraph[line[0]].insert(line[1]);
      inGraph[line[1]].insert(line[0]);
    }

    for (auto &node : outGraph) {
      if (node.second.empty()) {
        if (inGraph[node.first].size() == inGraph.size() - 1) {
          return node.first;
        }
      }
    }
    return -1;
  }
};

int main(int argc, char **argv) {
  //
  Solution            solution;
  vector<vector<int>> path = {{0, 3}, {1, 0}, {1, 3}, {2, 0}, {3, 0}, {3, 2}};
  cout << solution.transportationHub(path) << endl;
  return 0;
}