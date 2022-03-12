#include <iostream>
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <algorithm>
using std::max;
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring (string s) {
        size_t ret = 0, start = 0;
        unordered_map<char, size_t> map;
        for (int i = 0; i < s.size(); ++i) {
            auto found = map.find(s[i]);
            // 如果当前字符在表里
            if (found != map.end() && found->second >= start) {
                // 更新长度记录
                ret = max(ret, i - start);
                // 初始位置往后走一位
                start = found->second + 1;
            }
            // 记录<字符, 位置>
            map[s[i]] = i;
        }
        return max(ret, s.size() - start);
    }
};


int main() {

    Solution s;
    int result = s.lengthOfLongestSubstring("abcabcbbabcdeff");
    cout << result << endl;
    return 0;
}