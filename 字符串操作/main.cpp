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
    
    
    // 二分查找
    int binarySearch (vector<int> arr, int target) {
        
        if (arr.size() == 0) return -1;
        int left = 0, right = (int)arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] > target) {
                right = mid - 1;
            } else if (target > arr[mid]) {
                left = mid + 1;
            }
        }
        
        return -1;
    }
    
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
    
    // 是否包含子串
    bool isContainSubString(string str, string target) {
        bool result = false;
        int left(0), right(0), valid(0);
        int start(0), len = INT_MAX;
        unordered_map <char, int> need, window;
        for (char c : target) need[c]++;
        while (right < str.size()) {
            char tempS = str[right];
            // 窗口右移
            right++;
            if (need.count(tempS)) {
                // 设置窗口的值
                window[tempS]++;
                // 如果该字符的值与need的值相等，说明这个key符合要求
                if (window[tempS] == need[tempS]) {
                    valid++;
                }
            }
            // 如果 valid == need的大小 说明所有的字符都符合要求 有解了
            // 这是left 开始左移动， 寻找最优解
            while (valid == need.size()) {
                if (right - left < len) {
                    start = left;
                    len = right - left;
                }
                char delS = str[left];
                left++;
                if (need.count(delS)) {
                    if (window[delS] == need[delS]) {
                        valid--;
                    }
                    window[delS]--;
                }
            }
        }
        string s = str.substr(start, len);
        cout << "start: " << start << " -- len：" << len<< endl;
        cout << "result: " << s << endl;
        return false;
    }
    
    // 滑动窗口
    bool checkInclusion (string target, string s) {
        unordered_map<char, int> need, window;
        for (char c : target) need[c]++;
        int left(0), right(0);
        int varled(0);
        while (right < s.size()) {
            char tempS = s[right];
            right++;
            if (need.count(tempS)) {
                window[tempS]++;
                if (window[tempS] == need[tempS]) {
                    varled++;
                }
            }
            // 让窗口永远大于目标的大小
            while (right - left >= target.size()) {
                if (varled == need.size()) {
                    return true;
                }
                char d = s[left];
                left++;
                if (need.count(d)) {
                    if (need[d] == window[d]) {
                        varled--;
                    }
                    window[d]--;
                }
                
            }
            
        }
        
        return false;
    }
    
};


int main() {
    
    Solution s = Solution();
    
    // 1. 二分查找
//    vector<int> arr = {1, 2, 3, 4, 5, 6};
//    int target = 4;

//    int index =  s.binarySearch(arr, target);
//    cout << "结果"<< index << endl;
    
    // 2. 最长非重复子串
//    string str = "abbabcdce";
//    int result = s.longthOfLongestSubString(str);
    
//    // 2. 是否包含子串
//    string str = "eabfgabcdef";
//    string target = "abec";
//    int result = s.isContainSubString(str, target);
    
    
    //    // 2. 是否包含子串集合
        string str = "eidboaoo";
        string target = "da";
        int result = s.checkInclusion(target, str);
    
    cout << "结果"<< result << endl;
    return 0;
    
}
