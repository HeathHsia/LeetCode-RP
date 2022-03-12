#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

using namespace std;


/**
 * 最长回文子串
 */

class Solution
{
public:
    string longestPalindrome(string s) {
        // 如果字符串长度小于2
        if (s.size() < 2)
            return s;
        int max_len = 0, start = 0, i = 0;
        while (i < s.size()) {
            int r_ptr = i;
            int l_ptr = i;
            // 找到回文的中间值
            while (r_ptr < s.size() - 1 && s[r_ptr] == s[r_ptr + 1]) {
                r_ptr++;
            }
            i = r_ptr + 1;
            // 从中间向外找回文
            while (r_ptr < s.size() - 1 && l_ptr > 0 && s[r_ptr + 1] == s[l_ptr - 1]) {
                r_ptr++;
                l_ptr--;
            }
            int new_len = r_ptr - l_ptr + 1;
            // 更新最长记录子串长度和起始位置
            if (new_len > max_len) {
                start = l_ptr;
                max_len = new_len;
            }
        }

        return s.substr(start, max_len);
    }
};

int main() {

    string s = "cababacdefe";
    Solution solution;
    string result = solution.longestPalindrome(s);

    cout << result << endl;

    return 0;
}