#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  enum Direction { Up, Right, Down, Left };

  bool test(int row, int rows, int col, int cols, Direction direction,
            int depth, vector<string> &plate) {
    if (row < 0 || col < 0 || row >= rows || col >= cols) return false;
    if (plate[row][col] == 'O') return true;
    if (depth == 0) return false;
    if (plate[row][col] == '.') {
      switch (direction) {
        case Up:
          return test(row - 1, rows, col, cols, direction, depth - 1, plate);
        case Down:
          return test(row + 1, rows, col, cols, direction, depth - 1, plate);
        case Left:
          return test(row, rows, col - 1, cols, direction, depth - 1, plate);
        case Right:
          return test(row, rows, col + 1, cols, direction, depth - 1, plate);
      }
    }
    if (plate[row][col] == 'E') {
      // 顺时针
      switch (direction) {
        case Up:
          return test(row, rows, col + 1, cols, Right, depth - 1, plate);
        case Down:
          return test(row, rows, col - 1, cols, Left, depth - 1, plate);
        case Left:
          return test(row - 1, rows, col, cols, Up, depth - 1, plate);
        case Right:
          return test(row + 1, rows, col, cols, Down, depth - 1, plate);
      }
    }
    if (plate[row][col] == 'W') {
      // 逆时针
      switch (direction) {
        case Up:
          return test(row, rows, col - 1, cols, Left, depth - 1, plate);
        case Down:
          return test(row, rows, col + 1, cols, Right, depth - 1, plate);
        case Left:
          return test(row + 1, rows, col, cols, Down, depth - 1, plate);
        case Right:
          return test(row - 1, rows, col, cols, Up, depth - 1, plate);
      }
    }
    return false;
  }

  vector<vector<int>> ballGame(int num, vector<string> &plate) {
    int                 rows = plate.size();
    int                 cols = plate[0].size();
    vector<vector<int>> result;

    for (int i = 1; i < cols - 1; ++i) {
      if (plate[0][i] != 'O')
        if (test(0, rows, i, cols, Down, num, plate)) {
          result.push_back({0, i});
        }
      if (plate[rows - 1][i] != 'O')
        if (test(rows - 1, rows, i, cols, Up, num, plate)) {
          result.push_back({rows - 1, i});
        }
    }

    for (int i = 1; i < rows - 1; ++i) {
      if (plate[i][0] != 'O')
        if (test(i, rows, 0, cols, Right, num, plate)) {
          result.push_back({i, 0});
        }
      if (plate[i][cols - 1] != 'O')
        if (test(i, rows, cols - 1, cols, Left, num, plate)) {
          result.push_back({i, cols - 1});
        }
    }

    return result;
  }
};

int main(int argc, char **argv) {
  Solution solution;
  // vector<string> plate = {".....", "..E..", ".WO..", "....."};
  // vector<string> plate = {".....", "....O", "....O", "....."};
  // vector<string> plate = {"E...W..WW", ".E...O...", "...WO...W", "..OWW.O..",
  //                         ".W.WO.W.E", "O..O.W...", ".OO...W..",
  //                         "..EW.WEE."};
  vector<string> plate = {
      "E......O..", "E.........", "W..E...EW.", "EE.OE.WWWO", "O.WEOEWWW.",
      ".OW..W....", "W...EW.WE.", ".E.W...OW.", "OW...W.EEO", "......W.W."};
  auto result = solution.ballGame(76, plate);

  for (auto &list : result) {
    cout << "{";
    for (auto &item : list) {
      cout << item << " ";
    }
    cout << "}, ";
  }
  cout << endl;
  return 0;
}