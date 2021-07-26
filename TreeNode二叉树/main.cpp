#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <stack>
#include <vector>
#include <queue>

using namespace std;


/**
 节点 结构体
 */
struct Node {
    int val; // 节点当前值
    Node *left; // 左子树
    Node *right; // 右子树
    Node *next; // next 下一个
    Node (int x) : val(x), left(NULL), right(NULL), next(NULL){}
};

/**
 二叉树 结构体
 */
struct TreeNode {
    int val; // 节点当前值
    TreeNode *left; // 左子树
    TreeNode *right; // 右子树
    TreeNode (int x) : val(x), left(NULL), right(NULL){}
};


class Solution {
public:
    vector<int> postorderTraversal (TreeNode *root) {
        vector<int> retv;
        TreeNode *last = NULL;
        for (stack<TreeNode *>stk; root || !stk.empty(); ) {
            if (root) {
                stk.push(root);
                root = root->left;
            } else if (stk.top()->right && stk.top()->right != last) {
                root = stk.top()->right;
            } else {
                last = stk.top();
                retv.push_back(last->val);
                stk.pop();
            }
        }
        return retv;
    }
    
    // 二叉树的递归
    // 第一期
    // 1. 翻转二叉树
    TreeNode* invertTree(TreeNode* root) {
        
        // base case 退出递归循环
        if (root == nullptr) {
            return nullptr;
        }
        // 前序进行翻转，左右交换
        TreeNode* tempNode = root->left;
        root->left = root->right;
        root->right = tempNode;
        // 递归
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
    
    // 2. 节点左右用next连接
    Node* connect(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }
        connectLeftRight(root->left, root->right);
        return root;
    }
    // 连接左右子树
    void connectLeftRight(Node* left, Node* right) {
        if (left == NULL || right == NULL){
            return;
        }
        // 前序遍历，连接左右子树
        left->next = right;
        
        // 递归遍历二叉树
        // 连接左子树的左右
        connectLeftRight(left->left, left->right);
        // 连接右子树的左右
        connectLeftRight(right->left, right->right);
        // 连接左子树的右与右子树的左（非同父子树）
        connectLeftRight(left->right, right->left);
    }
    
    // 3. 将二叉树拉为链表(后序遍历)
    void flatten (TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        flatten(root->left);
        flatten(root->right);
        
        // 倒序递归遍历
        
        // 将左节点为null，左节点放到右子树的右节点
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        
        root->left = NULL;
        root->right = left;
        
        // 遍历到末端，放到右子树
        TreeNode *p = root;
        while (p->right != nullptr) {
            p = p->right;
        }
        p->right = right;
        
    }
    
    // 第二期
    // 4. 构造最大的二叉树
    // root 最为数组的最大值，左右子树都是分别左右子数组的最大值;
    TreeNode* constructMaximumBinaryTree(vector<int> nums) {
        return maxBuild(nums, 0 , (int)nums.size() - 1);
    }
    
    TreeNode* maxBuild(vector<int> nums, int l, int r) {
        if (l > r) {
            return nullptr;
        }
        int maxValue = INT_MIN;
        int maxIndex = -1;
        for (int i = l; i <= r; i++) {
            if (maxValue < nums[i]) {
                maxValue = nums[i];
                maxIndex = i;
            }
        }
        // 前序遍历
        TreeNode *root = new TreeNode(maxValue);
        // 递归查找左右子树 都是查找数组的最大值
        root->left = maxBuild(nums, l, maxIndex - 1);
        root->right = maxBuild(nums, maxIndex + 1, r);
        return root;
    }
    
    // 5.根据数组的前序遍历数组和中序数组还原二叉树
    // 前序整体结构是root[root->left][root->right]
    // 中序整体结构是[root->left]root[root->right]
    // 根据前序能找到root，再遍历中序获取root在中序的index
    // 中序可以获取到root->left区间的带下
    // 从而确定前序root->left和root->right的中间点
    TreeNode* buildTreeWithPreIn(vector<int> preorder, vector<int> inorder) {
        return buildTreeWithPreInBuild(preorder, 0, (int)preorder.size() - 1, inorder, 0, (int)inorder.size() - 1);
    }
    
    TreeNode* buildTreeWithPreInBuild (vector<int> preorder, int preStart, int preEnd, vector<int> inorder, int inStart, int inEnd) {
        if (preStart > preEnd) {
            return nullptr;
        }
        
        int rootValue = preorder[preStart];
        int inRootIndex = -1;
        for (int i = inStart; i <= inEnd; i++) {
            if (rootValue == inorder[i]) {
                inRootIndex = i;
            }
        }
        
        int leftSize = inRootIndex - inStart;
        
        TreeNode* root = new TreeNode(rootValue);
        root->left = buildTreeWithPreInBuild(
                    preorder, preStart + 1, preStart + leftSize,
                    inorder, inStart, inRootIndex - 1);
        root->right = buildTreeWithPreInBuild(
                    preorder, preStart + leftSize + 1, preEnd,
                    inorder, inRootIndex + 1, preEnd);
        return root;
    }
    
    // 6. 根据后序和中序获取二叉树
    // 同前序中序原理差不多，
    // 后序：[root->left][root->right]root
    // 中序: [root->left]root[root->right]
    TreeNode* buildTreeWithPostIn(vector<int> postOrder, vector<int>inOrder) {
        return buildTreeWithPostInBuild(postOrder, 0, (int)postOrder.size() - 1, inOrder, 0, (int)inOrder.size() - 1);
    }
    
    TreeNode* buildTreeWithPostInBuild(vector<int> postOrder, int postStart, int postEnd, vector<int> inOrder, int inStart, int inEnd) {
        if (postStart > postEnd) {
            return nullptr;
        }
        int rootValue = postOrder[postEnd];
        int inRootIndex = 0;
        for (int i = inStart; i<= inEnd; i++) {
            if (rootValue == inOrder[i]) {
                inRootIndex = i;
                break;
            }
        }
        int leftSize = inRootIndex - inStart;
        TreeNode* root = new TreeNode(rootValue);
        root->left = buildTreeWithPostInBuild(postOrder, postStart, postStart + leftSize, inOrder, inStart, inRootIndex - 1);
        root->right = buildTreeWithPostInBuild(postOrder, postStart + leftSize + 1, postEnd - 1, inOrder, inRootIndex + 1, inEnd);
        return root;
    }
    
    // ****BST 二叉搜索树 binary search tree
    // 左子树比root小，右子树比root大
    // 中序遍历正好是升序
    // 解决方案都是按这俩特性走的
    
    // 经典BST二叉搜索树的框架
    // 因为左小右大的特性，
    // 如果比目标值大，说明要从左子树开始往小了找
    // 如果比目标值小，说明要从右子树开始往大了找
    void BST (TreeNode* root, int target) {
        if (root == nullptr) return;
        if (root->val == target) return;
        if (root->val > target) {
            BST(root->left, target);
        }
        if (root->val < target) {
            BST(root->right, target);
        }
    }
    
    // 1. 获取第k大的元素

    int kthSmallest_res = 0;
    int kthSmallest_count = 0;
    
    int kthSmallest (TreeNode* root, int k) {
        kthSmallest_build(root, k);
        return kthSmallest_res;
    }
    
    void kthSmallest_build(TreeNode* root, int k) {
        if (root == nullptr) {
            return;
        }
        kthSmallest_build(root->left, k);
        // 中序遍历是升序，找到第k个节点
        kthSmallest_count++;
        if (kthSmallest_count == k) {
            kthSmallest_res = root->val;
        }
        kthSmallest_build(root->right, k);
    }
    
    
    // 2. 将二叉搜索树BST转化为累加和树
    int convertBST_sum = 0;
    TreeNode* convertBST(TreeNode* root) {
        convertBST_build(root);
        return root;
    }

    void convertBST_build(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        convertBST(root->right);
        convertBST_sum += root->val;
        root->val = convertBST_sum;
        convertBST(root->left);
    }
    
    // 3. 判断二叉搜索树的合法性
    // root的整个左子树都要比root小，右子树比root大
    
    bool isValidBST (TreeNode* root) {
        return isValidBST_build(root, nullptr, nullptr);
    }
    
    bool isValidBST_build(TreeNode* root, TreeNode* min, TreeNode* max) {
        if (root == nullptr) {
            return true;
        }
        // 满足：max->val > root->val > min->val;
        if (min != nullptr && root->val <= min->val) {
            return false;
        }
        if (max != nullptr && root->val >= max->val) {
            return false;
        }
        // 注意这里继续传min和max
        return isValidBST_build(root->left, min, root)
                && isValidBST_build(root->right, root, max);
    }
    
    // 4. 二叉搜素树BST查找某个数
    bool isInBST(TreeNode* root, int target) {
        if (root == nullptr) {
            return false;
        }
        if (root->val == target) {
            return true;
        }
        if (root->val > target) {
            return isInBST(root->left, target);
        } else {
            return isInBST(root->right, target);
        }
    }
    
    // 5. 二叉搜索树BST插入一个树节点
    // 函数返回的是节点，需要返回值进行接收
    TreeNode* insertBST (TreeNode* root, int target) {
        if (root == nullptr) {
            return new TreeNode(target);
        }
        if (root->val > target) {
            root->left = insertBST(root->left, target);
        } else {
            
            root->right = insertBST(root->right, target);
        }
        // 返回根节点
        return root;
    }
    
    // 6. 二叉搜索树删除一个节点
    TreeNode* delBST (TreeNode* root, int target) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->val == target) {
            if (root->left == nullptr) {
                // 如果左子树为空，直接返回右子树
                return root->right;
            }
            if (root->right == nullptr) {
                // 如果右子树为空，直接返回左子树
                return root->left;
            }
            // 如果左右子树都有，需要找到右子树的最小值
            TreeNode* minNode = delBSTMin(root->right);
            root->val = minNode->val;
            root->right = delBST(root->right, minNode->val);
        } else if (root->val > target) {
            root->left =  delBST(root->left, target);
        } else {
            root->right = delBST(root->right, target);
        }
        return root;
    }
    // 找到右子树最小值节点
    TreeNode* delBSTMin (TreeNode* root) {
        // BST 最左边的就是最小的
        return root->left != nullptr ? delBSTMin(root->left) : root;
    }
    
    // 7. 不同的二叉搜索树 给定一个值获取二叉搜索树的情况
    // 增加备忘录，重复子问题
    vector<vector<int>> memo;
    int numsBST (int n) {
        memo = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
        return numsBST_build(1, n);
    }
    
    int numsBST_build(int start, int end) {
        if (start > end) {
            return 1;
        }
        if (memo[start][end] != 0) {
            return memo[start][end];
        }
        int numsBST_res = 0;
        for (int i = start; i <= end; i++) {
            // i 作为root节点
            int left = numsBST_build(start, i - 1);
            int right = numsBST_build(i + 1, end);
            
            // 左右子树的组合树乘积是BST的总数
            numsBST_res += left * right;
        }
        memo[start][end] = numsBST_res;
        return numsBST_res;
    }
    // 8. 不同的二叉搜索树的结果结合
    vector<TreeNode* > generateTrees (int n) {
        if (n == 0) {
            return vector<TreeNode* >();
        }
        return generateTrees_build(1, n);
    }
    
    vector<TreeNode* >generateTrees_build (int l, int r) {
        vector<TreeNode* > res = vector<TreeNode *>();
        if (l > r) {
            res.push_back(nullptr);
            return res;
        }
        for (int i = l; l <= r; i++) {
            vector<TreeNode* >leftTree = generateTrees_build(l, i - 1);
            vector<TreeNode* >rightTree = generateTrees_build(i + 1, r);
            for (TreeNode* left : leftTree) {
                for (TreeNode* right : rightTree) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
    
    
    
    //################ 迭代法遍历
    // 1. 前序遍历 中->左->右
    vector<int> preOrderTravelsal (TreeNode *root) {
        // 定义一个数组
        vector<int> ans;
        // 栈
        stack<TreeNode *>stk;
        // 将根节点入栈
        stk.push(root);
        // 如果栈不为空的话，循环
        while (!stk.empty()) {
            // 取出栈顶
            TreeNode *node = stk.top();
            // 存到数组中
            ans.push_back(node->val);
            // 移除栈顶
            stk.pop();
            // 因为栈是后进先出，所以先让右节点先进
            if (node->right != NULL) {
                stk.push(node->right);
            }
            // 右节点进完再进左节点
            if (node->left != NULL) {
                stk.push(node->left);
            }
        }
        return ans;
    }
    
    // 2. 中序遍历 左->中->右
    vector<int> inOrderTravelsal (TreeNode *root) {
        // 定义一个数组
        vector<int> ans;
        // 栈
        stack<TreeNode *>stk;
        // 如果栈不为空的话，循环
        while (!stk.empty() || root != NULL) {
            while (root != NULL) {
                stk.push(root);
                root = root->left;
            }
            TreeNode *node = stk.top();
            stk.pop();
            ans.push_back(node->val);
            root = node->right;
        }
        return ans;
    }
    
    // 3. 后序遍历 左->右->中
    vector<int> postOrderTravelsal (TreeNode *root) {
        vector<int> ans;
        TreeNode *pre = NULL;
        stack<TreeNode *> stk;
        while (!stk.empty() || root != NULL) {
            while (root != NULL) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (root->right == NULL || root->right == pre) {
                ans.push_back(root->val);
                pre = root;
                root = NULL;
            } else {
                stk.push(root);
                root = root->right;
            }
        }
        return ans;
    }
    
    // 4. 层序遍历
    vector<vector<int>> levelOrder (TreeNode *root) {
        vector<vector<int>> ret;
        if(!root) return ret;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int currentLevelSize = (int)q.size();
            ret.push_back(vector<int>());
            for (int i = 0; i < currentLevelSize; i++) {
                auto node = q.front();
                q.pop();
                ret.back().push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return ret;
    }
};


int main() {

    // 创建树
    /**
                1
            2       3
          4   5   6   7
     */
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
    node2.left = &node5;
    node2.right = &node6;
    
    
    /**
                1
            2       3
          4   5   6   7
     */
    
    Solution s;
//    for (auto i : s.levelOrder(&root)) {
//        cout << i << " ";
//    }
    // 1. 二叉树的翻转
//    TreeNode* node = s.invertTree(&root);
    
    // 2. 二叉树拉伸为链表
    s.flatten(&root);
    
    // 层序遍历 打印二叉树
    for (auto i : s.levelOrder(&root)) {
        for (auto j : i) {
            cout << j << " ";
        }
    }
    cout << "" << endl;
    return 0;
    
}
