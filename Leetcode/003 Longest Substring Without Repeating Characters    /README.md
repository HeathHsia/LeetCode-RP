### [Longest Substring Without Repeating Characters ](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

求字符串无重复的最长子串

给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

- eg：输入: "abcabcbb"
- 输出: 3 
- 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

> 1. 遍历字符串，用hash表存储<字符，坐标>
> 2. 如果字符在hash表中存在的话，更新记录子串长度和起始坐标
> 3. 子串长度=当前坐标-起始坐标


