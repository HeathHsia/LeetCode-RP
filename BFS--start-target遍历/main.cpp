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


TreeNode createTreeNode () {
    TreeNode root(1);
    TreeNode node1(2);
    TreeNode node2(3);
    TreeNode node3(4);
    TreeNode node4(5);
    TreeNode node5(6);
    TreeNode node6(7);
    root.left = &node1;
    root.right = &node2;
//    node1.left = &node3;
//    node1.right = &node4;
    node2.left = &node5;
    node2.right = &node6;
    return  root;
}



class Solution {
public:
    
    // BFS 算法
    // 在一个图中，从start到target中找到最小距离
    
    // 1. 二叉树最小深度
    // BFS算法
    int minDepth (TreeNode *root) {
        int depth = 1;
        queue<TreeNode *> queue;
        queue.push(root);
        while (!queue.empty()) {
            // 确保当前队列中所有的节点都会遍历过
            // 这里不能直接使用queue.size 因为queue实时动态的增加节点
            // 每轮固定大小遍历
            int sz = (int)queue.size();
            for (int i = 0; i < sz; i++) {
                TreeNode *top = queue.front();
                queue.pop();
                if (top->left == nullptr && top->right == nullptr) {
                    return depth;
                }
                if (top->left != nullptr) {
                    queue.push(top->left);
                }
                if (top->right != nullptr) {
                    queue.push(top->right);
                }
            }
            // 步数+1
            depth++;
        }
        return depth;
    }
    
    // 2. 猜4位密码
    int openLock (vector<string> deadends, string target) {
        set<string> deads;
        for (string dead : deadends) deads.insert(dead);
        set<string> visiteds;
        queue<string> q;
        q.push("0000");
        visiteds.insert("0000");
        int step = 0;
        while (!q.empty()) {
            int sz = (int)q.size();
            // 遍历当前的栈
            for (int i = 0; i < sz; i++) {
                string cur = q.front();
                q.pop();
                // 如果当前的节点属于死亡锁区间，则继续
                if (deads.count(cur) != 0) {
                    continue;
                }
                // 判断当前是否是终点，直接返回
                if (cur == target) {
                    return step;
                }
                for (int j = 0; j < 4; j++) {
                    string upStr = plusUp(cur, j);
                    if (visiteds.count(upStr) == 0) {
                        q.push(upStr);
                        visiteds.insert(upStr);
                    }
                    string downStr = plusDown(cur, j);
                    if (visiteds.count(downStr) == 0) {
                        q.push(downStr);
                        visiteds.insert(downStr);
                    }
                }
            }
            step++;
        }
        
        return -1;
    }
    
    // 向上拨动
    string plusUp (string str, int index) {
        char c = str[index];
        if ('9' == c) {
            c = '0';
        } else {
            c += 1;
        }
        str[index] = c;
        return str;
    }
    
    // 向下拨动
    string plusDown (string str, int index) {
        char c = str[index];
        if ('0' == c) {
            c = '9';
        } else {
            c -= 1;
        }
        str[index] = c;
        return str;
    }
    
    
    // 二叉树最小深度 递归方法
//    int minDepth (TreeNode *root) {
//        if (root == nullptr) {
//            return 0;
//        } else if (root->left == nullptr) {
//            return minDepth(root->right) + 1;
//        } else if (root->right == nullptr) {
//            return minDepth(root->left) + 1;
//        } else {
//            return min(minDepth(root->left), minDepth(root->right)) + 1;
//        }
//    }
    
    
    
};


int main() {
    
    Solution s = Solution();
    
    
    // 1. 最长回文子串
//    TreeNode root = createTreeNode();
    
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
    
    
    
//    int res = s.minDepth(&root);
    

//    cout << "结果"<< res << endl;
    
    
    string target = "1929";
    vector<string> dead = vector<string>();
    int result = s.openLock(dead, target);
    cout << "结果"<< result << endl;
    
    return 0;
    
}
