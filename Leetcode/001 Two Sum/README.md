### [Two Sum](https://leetcode.com/problems/two-sum/)

两数之和

已知数组求两数之和为target的坐标数组

- eg: nums = [2, 7, 11, 15] target 9, nums[0] + nums[1] = 9, return [0, 1]

> 1. 遍历数组，用hash表存储<值，index>
> 2. 判断hash中是否存在target - nums[i]的值

