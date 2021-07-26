#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <stack>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;


class Solution {
public:
    
    
    //  003. 最长非重复子串 abbabcdce
    // 滑动窗口
    int longthOfLongestSubString(string s) {
        unordered_map<char, int> window;
        int left(0), right(0), result(0);
        while (right < s.size()) {
            char tempS = s[right];
            // 窗口右移
            right++;
            window[tempS]++;
            // 判断左是否移动，有重复的了(大于1)
            while (window[tempS] > 1) {
                char d = s[left];
                left++;
                window[d]--;
            }
            result = max(result, right - left);
            
        }
        return result;
    }
    
    // 005 字符串： 最长子回文串
    // 动态规划
    // 中心扩散法
    string panlindrome(string &s, int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            // 从中心往两边进行扩散
            l--;
            r++;
        }
        return s.substr(l + 1, r - l - 1);
    }
    
    string longestPanlindrome (string str) {
        string result = "";
        for (int i = 0; i < str.size(); i++) {
            string s1 = panlindrome(str, i, i);
            string s2 = panlindrome(str, i, i + 1);
            result = result.size() > s1.size() ? result : s1;
            result = result.size() > s2.size() ? result : s2;
        }
        return result;
    }
    
    // 动态规划
    
    // 斐波那契数列：每一项是前两项的和
    int Fib (int n) {
        if (n < 1) return 0;
        if (n == 1 || n == 2) return 1;
        vector<int> dp(n + 1, 0);
        dp[1] = dp[2] = 1;
        for (int j = 3; j <= n; j++) {
            // 当前的数据是前两的和
            dp[j] = dp[j - 1] + dp[j - 2];
        }
        return dp[n];
    }
    
    // 零钱分配问题
    int coinChange (vector<int> coins, int target) {
        if (target == 0) return  0;
        if (target < 0) return -1;
        vector<int> dp (target + 1, target + 1);
        dp[0] = 0;
        for (int i = 0; i < dp.size(); i++) {
            for (int coin : coins) {
                if ((i - coin) < 0) continue;
                dp[i] = min(dp[i], 1 + dp[i - coin]);
            }
        }
        return (dp[target] ==  target + 1) ? -1 : dp[target];
    }
      
};


int main() {
    
    Solution s = Solution();
    
    
    // 1. 斐波那契列数组
//    int result = s.Fib(5);
    
    // 2. 零钱问题
//    vector<int> coins = {1, 2, 5};
//    int target = 11;
//    int result = s.coinChange(coins, target);
    
    // 3. 最长回文子串
    string str = "aa";
    string result = s.longestPanlindrome(str);
    
    cout << "结果"<< result << endl;
    return 0;
    
}
