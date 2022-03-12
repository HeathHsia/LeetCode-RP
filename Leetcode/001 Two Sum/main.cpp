#include <iostream>
#include <vector>
#import <unordered_map>
using std::vector;
using std::unordered_map;
using namespace std;


/**
 * 两数之和
 * 已知数组，求两数之和为target的坐标数组
 * eg: nums = [2, 7, 11, 15] target 9, nums[0] + nums[1] = 9, return [0, 1]
 *
 * 1. 遍历数组，用hash表存储<值，index>
 * 2. 判断hash中是否存在target - nums[i]的key
 */

class Solution {
public:
    vector<int> twoSum (vector<int>& nums, int target) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            int com = target - nums[i];
            auto found = map.find(com);
            if (found != map.end()) {
                return {found->second, i};
            }
            map.emplace(nums[i], i);
        }
        return {1, 1};
    }
};

int main() {
    vector<int> arr = {1, 2, 4, 3, 6};
    int target = 8;
    Solution s;
    vector<int> result = s.twoSum(arr, target);
    vector<int>::iterator i;
    for (i = result.begin(); i != result.end(); ++i)
        cout << "" << *i << endl;
    return 0;
}

