#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;
using namespace std;

/**
 * Z字形变换
 */

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1) return s;
        vector<string> db (numRows, "");
        for (int i = 0, row = 0, step = 1; i < s.size(); i++) {
            // row 行数
            // step ： 当row为0时，需要向下递增step=1
            //      ： 当row增加到值为numRows时，需要向上递减step=-1
            // 当前字符加入到对应行的字符串中
            db[row] += s[i];
            if (row == 0) step = 1;
            if (row == numRows - 1) step = -1;
            row += step;
        }
        string ret;
        for (auto d : db) {
            ret += d;
        }
        return ret;
    }
};

int main() {

    string str = "LEETCODEISHIRING";
    int numRows = 4;

    Solution s;
    string result = s.convert(str, numRows);

    cout << result << endl;

    return 0;
}