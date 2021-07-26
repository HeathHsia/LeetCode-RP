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
    
    // 回溯算法：决策树算法：暴力回归
    // 可选择列表：
    // 结束条件：比如说 当前结果列表与初始列表个数相等
    
    // 1.  求全排列的代码：
    vector<vector<int>> res;
    
    vector<vector<int>> premute (vector<int> nums) {
        vector<int> track;
        backtrack(nums, track);
        
        
        return res;
    }
    
    void backtrack (vector<int> nums, vector<int> track) {
        
        cout << "进入到backtrack函数中=======" << endl;
        if (track.size() == nums.size()) {
            cout << "track 加入 到 res中" << endl;
            res.push_back(track);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            // 如果包含nums[i] 则继续遍历
            cout << "遍历当前 nums[i] == "<< nums[i] << "  i == "<< i << endl;

            if (std::find(track.begin(), track.end(), nums[i]) != track.end()) {
                cout << "nums[i] == " << nums[i] << "已经在track存在了" << endl;
                continue;
            }
            // 递归先执行这几个
            cout << "track 加入 nums[i] == "<< nums[i] << endl;
            track.push_back(nums[i]);
            backtrack(nums, track);
            cout << "track 移除掉 nums[i] == "<< nums[i] << endl;
            // 取消选择(递归完之后清空)
            track.pop_back();
        }
    }
    
    // 2. N皇后问题
    
    
};


int main() {
    
    Solution s = Solution();
    
    
    // 1. 最长回文子串
    vector<int> arr = {1, 3, 4};
    vector<vector<int>> res = s.premute(arr);
    
    
//    cout << "结果"<< res << endl;
    return 0;
    
}
