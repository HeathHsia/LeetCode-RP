#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <stack>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>

using namespace std;


/**
 二叉树 结构体
 */
struct TreeNode {
    int val; // 节点当前值
    TreeNode *left; // 左子树
    TreeNode *right; // 右子树
    TreeNode (int x) : val(x), left(nullptr), right(nullptr){}
};


class Solution {
public:
    
    // 股票买卖类型题
    // dp 动态规划 状态转移方程
    // dp[i][k][0]
    // i： 第几天
    // k： 交易第几次 // 卖出时还是k次；买入的时候k-1次
    // 0/1：0代表未持有股票, 1代表持有股票
    // + price[i] 卖出股票；-prices[i] 购入购票
    /**
        dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
        第i天交易k次手里没有股票:
            前一天(i-1)，没有股票 = dp[i-1][k][0]
            前一天(i-1)，有股票卖掉了 = dp[i-1][k][1] + prices[i]
        
     
        dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
        第i天交易k次手里有股票：
            前一天(i-1)，有股票 = dp[i-1][k][1]
            前一天(i-1)，没有股票买入了 = dp[i-1][k - 1][0] - prices[i]
        
     */
    
    
    // 1. 只能交易一次 k == 1
    int maxProfit (vector<int> prices) {
        int n = (int)prices.size();
//        int dp[n][2];
        // dp状态方程也可以使用局部变量进行代替
        int dp_i0 = 0;
        int dp_i1 = INT_MIN;
        for (int i = 0; i < n; i++) {
            int temp = dp_i0;
            dp_i0 = max(dp_i0, dp_i1 + prices[i]);
            dp_i1 = max(dp_i1, temp - prices[i]);
        }
        return dp_i0;
    }
    
    // 2. 可以交易无数次
    int maxProfit_kMax (vector<int> prices) {
        int n = (int)prices.size();
        int dp_i0 = 0;
        int dp_i1 = INT_MIN;
        for (int i = 0; i < n; i++) {
            int temp = dp_i0;
            dp_i0 = max(dp_i0, dp_i1 + prices[i]);
            dp_i1 = max(dp_i1, temp - prices[i]);
        }
        return dp_i0;
    }
    
    // 3. 只可以交易两次
    int maxProfit_kTwo (vector<int> prices) {
        int n = (int)prices.size();
        int dp_i20 = 0, dp_i21 = INT_MIN;
        int dp_i10 = 0, dp_i11 = INT_MIN;
        for (int i = 0; i < n; i++) {
            dp_i20 = max(dp_i20, dp_i21 + prices[i]);
            dp_i21 = max(dp_i21, dp_i10 - prices[i]);
            dp_i10 = max(dp_i10, dp_i11 + prices[i]);
            dp_i11 = max(dp_i11, -prices[i]);
        }
        return dp_i20;
    }
    
    // 4. 交易有手续费 free
    int maxProfit_fee (vector<int> prices) {
        int n = (int)prices.size();
        int fee = 4;
        int dp_i0 = 0 ;
        int dp_i1 = INT_MIN;
        for (int i = 0; i < n; i++) {
            int temp = dp_i0;
            dp_i0 = max(dp_i0, dp_i1 + prices[i]);
            dp_i1 = max(dp_i1, temp - prices[i] - fee);
        }
        return dp_i0;
    }
    
    // 5. 交易有冷却期限
    int maxProfit_with_cool (vector<int> prices) {
        int n = (int)prices.size();
        int dp_i0 = 0;
        int dp_pre = 0;
        int dp_i1 = INT_MIN;
        for (int i = 0; i < n; i++) {
            int temp = dp_i0;
            dp_i0 = max(dp_i0, dp_i1 + prices[i]);
            dp_i1 = max(dp_i1, dp_pre - prices[i]);
            dp_pre = temp;
        }
        return dp_i1;
    }
    
    // 6. k取最大值
    
    
    // 打家劫舍
    // 1. 不能连续打劫, 求抢劫最大值
    unordered_map<int, int> meto;
    // dp 算法
    int rob (vector<int> nums) {
        // 备忘录
        int res = dp(nums, 0);
        return res;
    }
    int dp (vector<int>nums, int start) {
        if (start >= nums.size()) {
            return 0;
        }
        if (meto.count(start) != 0) {
            return meto[start];
        }
        int res = max(dp(nums, start + 1), nums[start] + dp(nums, start + 2));
        meto[start] = res;
        return res;
    }
    
    // 2. 环形数组，首尾不能同时抢劫
    int rob_ann (vector<int> nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        int res = max(dp_ann(nums, 0, (int)nums.size() - 2), dp_ann(nums, 1, (int)nums.size() - 1));
        return res;
    };
    
    int dp_ann(vector<int> nums, int start, int end) {
        int cur = 0;
        int pre = 0;
        for (int i = start; i <= end; i++) {
            int temp = max(cur, nums[i] + pre);
            pre = cur;
            cur = temp;
        }
        return cur;
    }
    // 简化算法
//    int rob (vector<int> nums) {
//        int pre = 0;
//        int cur = 0;
//        for (int i = 0; i < nums.size(); i++) {
//            cout << "当前第" << i + 1 << "次" << endl;
//            cout << "没偷==" << cur << endl;
//            cout << "偷了==" << pre + nums[i] << endl;
//            // dp 不能去纠结真正的过程，而是列状态和选择
//            // 状态就是k个
//            // 选择就是偷还是不偷
//            int temp = max(cur, pre + nums[i]);
//            pre = cur;
//            cur = temp;
//        }
//        return cur;
//    }
    
    
};


int main() {
    
    Solution s = Solution();

    TreeNode root(1);
    TreeNode node1(2);
    TreeNode node2(3);
    TreeNode node3(4);
    TreeNode node4(5);
    TreeNode node5(6);
    TreeNode node6(7);
    root.left = &node1;
    root.right = &node2;
    node1.left = &node3;
    node1.right = &node4;
//    node2.left = &node5;
//    node2.right = &node6;
    
    // 1 k=1 只能交易一次
//    vector<int> arr = {1,2,3,4,5};
//    vector<int> arr = {7, 1, 3, 4, 5};
    
    // 2. k=无数次 可以交易无数次
//    vector<int> arr = {7,1,5,3,6,4}; // 7
//    vector<int> arr = {1,2,3,4,5};  // 4
//    vector<int> arr = {7,6,4,3,1};  // 0
    
    
    // 3. k = 2 只可以交易两次
//    vector<int> arr = {3,3,5,0,0,3,1,4}; // 6
//    vector<int> arr = {1,2,3,4,5};  // 4
//    vector<int> arr = {7,6,4,3,1};  // 0
    
    // 4. 可以交易k次
    
    
    // 打家劫舍
    // 1. 不能连续打劫
//    vector<int> arr = {2, 1, 1, 2};
//    vector<int> arr = {1,2,3,1};
//    vector<int> arr = {2,7,9,3,1};
    
    // 2. 打家劫舍 环形数组
    vector<int> arr = {1,2,3,1};
    
    
    
    // 1. 可以交易一次
//    int res = s.maxProfit(arr);
    
    // 2 可以交易无数次
//    int res = s.maxProfit_kMax(arr);
    
    // 3 可以交易两次
//    int res = s.maxProfit_kTwo(arr);

//    int res = s.rob(arr);
    
    int res = s.rob_ann(arr);
    
    
    cout << "结果"<< res << endl;
    
    
    return 0;
    
}
