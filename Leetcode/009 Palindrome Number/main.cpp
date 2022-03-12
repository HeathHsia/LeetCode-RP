#include <iostream>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        // 负数不是回文数
        // 最后一位是0的也不是回文数
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        int rev = 0;
        while (x > rev) {
            rev = rev * 10 + x % 10;
            x /= 10;
        }
        // 数字为偶数位则相等
        // 数字为奇数位则去要去掉中位数再比较
        return x == rev || x == rev / 10;
    }
};

int main() {

    int num = 121;
    Solution s;
    bool result = s.isPalindrome(num);
    cout << result << endl;

    return 0;
}