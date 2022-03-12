#include <iostream>
using namespace std;

/**
 * 整型翻转
 */

class Solution{
public:
    int reverse(int x) {
        long long res = 0;
        do {
            // res*10 保证先获取的值为最高
            // x%10 保证一致取的是x的个位(最后一位)
            // x/10 裁剪原数
            res = res * 10 + x % 10;
        }while (x /= 10);
        // 防止溢出
        return (res < INT_MIN || res > INT_MAX) ? 0 : res;
    }
};

int main() {

    int num = -123;
    Solution s;
    int result = s.reverse(num);
    cout << result << endl;

    return 0;
}