#include "common.h"

class Solution {
public:
    int maximumLength(string s) {
        // 只需记录超过 3 的最长的字符串
        vector<vector<int>> len(26, vector<int>());
        for (int i = 0; i < s.size(); i++) {
            for (int j = i; i + j < s.size() && s[i] == s[i + j]; j++) {
                len[s[i] - 'a'].emplace_back(j - i + 1);
            }
        }

        int max_cnt = -1;

        for (int i = 0; i < 26; i++) {
            sort(len[i].begin(), len[i].end(), greater<int>());
            for (int j = 0; j + 2 < len[i].size(); ++j) {
                if (len[i][j] == len[i][j + 1] && len[i][j + 1] == len[i][j + 2]) {
                    max_cnt = max(max_cnt, len[i][j]);
                }
            }
        }
        return max_cnt;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    print(so.maximumLength("aaaa"));
    return 0;
}
