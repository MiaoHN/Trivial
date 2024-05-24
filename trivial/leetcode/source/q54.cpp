#include "common.h"

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int m = matrix.size();
        int n = matrix[0].size();

        for (int i = 0; i < m * n; ++i) {
            auto pos = get(m, n, i);
            res.push_back(matrix[pos[0]][pos[1]]);
        }
        return res;
    }

    vector<int> get(int m, int n, int i) {
        vector<int> pos[2];

        int dir = 0; // 0 → 1 ↓ 2 ← 3 ↑
        int cl = 0, cr = n - 1;
        int rt = 0, rb = m - 1;

        while (i > 0 && cl <= cr && rt <= rb) {
            if (dir == 0) {
                int d = cr - cl;
                if (d >= i) {
                    return {rt, cl + i};
                } else {
                    i -= d + 1;
                    rt++;
                    dir = 1;
                }
            } else if (dir == 1) {
                int d = rb - rt;
                if (d >= i) {
                    return {rt + i, cr};
                } else {
                    i -= d + 1;
                    cr--;
                    dir = 2;
                }
            } else if (dir == 2) {
                int d = cr - cl;
                if (d >= i) {
                    return {rb, cr - i};
                } else {
                    i -= d + 1;
                    rb--;
                    dir = 3;
                }
            } else if (dir == 3) {
                int d = rb - rt;
                if (d >= i) {
                    return {rb - i, cl};
                } else {
                    i -= d + 1;
                    cl++;
                    dir = 0;
                }
            }
        }

        return {0, 0};
    }
};

int main(int argc, char const *argv[])
{
    Solution solution;
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    print(solution.spiralOrder(matrix));
    return 0;
}