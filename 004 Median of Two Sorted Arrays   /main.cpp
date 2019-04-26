#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>

using std::vector;
using std::max;
using std::min;
using namespace std;

/**
 * 中位数会同时满足两个条件
 * 1. 左部分个数 == 右部分个数
 * 2. 左部分最大数 <= 右部分最小数
 */

class Solution{
public:
    double findMedianSortedArrays (vector<int> nums1, vector<int> nums2) {
        int m = nums1.size();
        int n = nums2.size();
        if (m > n) {
            // 保证n > m
            vector<int> tempArr = nums1; nums1 = nums2; nums2 = tempArr;
            int tempInt = m; m = n; n = tempInt;
        }
        int iMin = 0, iMax = m, halfLen = (m + n + 1) / 2;
        while (iMin <= iMax) {
            int i = (iMin + iMax) / 2;
            int j = halfLen - i;
            if (i < iMax && nums2[j - 1] > nums1[i]) {
                iMin = i + 1; // i太小
            }
            else if (i > iMin && nums1[i - 1] > nums2[j]) {
                iMax = i - 1; // i太大
            } else {
                // i正好
                // 左边部分最大值
                int maxLeft = 0;

                // 三种情况
                if (i == 0) {
                    maxLeft = nums2[j - 1];
                } else if (j == 0) {
                    maxLeft = nums1[i - 1];
                } else {
                    maxLeft = max(nums2[j - 1], nums1[i - 1]);
                }

                // 如果B和A的个数和为奇数的话，左边最大值为中位数
                if ((m + n) % 2 == 1) {
                    return maxLeft;
                }

                // 右边部分最小值
                int minRight = 0;

                // 三种情况
                if (i == m) {
                    minRight = nums2[j];
                } else if (j == n) {
                    minRight = nums1[i];
                } else {
                    minRight = min(nums2[j], nums1[i]);
                }

                return (maxLeft + minRight) / 2.0;
            }
        }
        return 0.0;
    }
};

// 寻找两个有序数组的中位数

int main() {
    vector<int> l1 = {};
    vector<int> l2 = {2, 3};
    Solution s;
    double result = s.findMedianSortedArrays(l1, l2);
    cout << setprecision(10) << result << endl;
    return 0;
}