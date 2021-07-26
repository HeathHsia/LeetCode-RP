#include <iostream>
#include <cstddef>
#include <cstdlib>

using namespace std;

/**
 链表节点
 */
struct ListNode {
    int var; // 节点当前值
    ListNode *next; // 指向的下一个节点
    ListNode (int x) : var(x), next(NULL) {}
};

/**
 创建链表
 */

ListNode* create_linkedlist (std::initializer_list<int> list) {
    auto iter = list.begin();
    ListNode *head = list.size() ? new ListNode(*iter++) : NULL;
    for (ListNode *cur=head; iter!=list.end(); cur=cur->next) {
        cur->next = new ListNode(*iter++);
    }
    return head;
}


class Solution {
public:
    // 1. 删除倒数第n个节点 LeetCode 19
    // https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/
    // 1->3->4->5  倒数第二个
    // 1->3->5
    ListNode* deleteNthFromEnd(ListNode *head, int n) {
        auto dummy = new ListNode(-1);
        dummy->next = head;
        auto first = dummy, second = dummy;
        while (n--) {
            // 先将first指针移动n个，与second保持n个距离
            first = first->next;
        }
        while (first->next) {
            // 再一起移动first和second，直到first指向空，那么second就是倒数n-1个
            first = first->next;
            second = second->next;
        }
        // 倒是第n-1个指向倒数下两个就成功删除掉第n个了。
        second->next = second->next->next;
        return dummy->next;
    }
    
    // 2. 删除某个指定的节点 ListNode 237
    // https://leetcode.com/problems/delete-node-in-a-linked-list/
    void deleteWithVal(ListNode *node) {
        // 把当前节点的值换成下一个节点的值
        // 指针指向下一个节点所指向的节点
//        node->var = node->next->var;
//        node->next = node->next->next;
        
        // 将节点的指针指向下一个节点的地址
        *node = *(node->next);
    }
    
    // 3. 删除有序链表中的重复的元素 LeetCode 83
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list/
    ListNode* deleteDuplicates(ListNode *head) {
        auto dummy = head;
        while (dummy) {
            // 链表的遍历
            if (dummy->next && dummy->var == dummy->next->var) {
                dummy->next = dummy->next->next;
            } else {
                dummy = dummy->next;
            }
        }
        return head;
    }
    
    
    // 4. 链表向右旋转n个节点 LeetCode 61
    // https://leetcode-cn.com/problems/rotate-list/
    ListNode* rotateRight(ListNode *head, int k) {
        if (!head) {
            return NULL;
        }
        int n = 0;
        for (auto p=head; p; p=p->next) {
            // 获取链表的长度
            n++;
        }
        // 找到要翻转的位置
        k %= n;
        auto first = head, second = head;
        while (k--) {
            // 拿到要翻转的
            first = first->next;
        }
        while (first->next) {
            first = first->next;
            second = second->next;
        }
        first->next = head;
        head = second->next;
        second->next = NULL;
        
        return head;
        
    }
    
    // 5. 两两交换链表中的节点 LeetCode 24
    // https://leetcode-cn.com/problems/swap-nodes-in-pairs/
    ListNode* exchangeListNode(ListNode *head) {
        auto dummy = new ListNode(-1);
        dummy->next = head;
        for (auto p = dummy; p->next && p->next->next; p=p->next->next) {
            auto a = p->next, b = a->next;
            p->next = b;
            a->next = b->next;
            b->next = a;
        }
        return dummy->next;
    }
    
    // 6. 反转链表 LeetCode 202
    ListNode* reverse(ListNode *head) {
        if (!head) return NULL;
        auto a = head, b = head->next;
        while (b) {
            auto c = b->next;
            b->next = a; // 当前节点指向前一个
            a = b; // 指针后移
            b = c; // 指针后移
        }
        head->next = NULL;
        return a;
    }
    
    // 7. 反转链表 LeetCode 92
    // 从m-n进行反转
    ListNode* reverseFromMtoN(ListNode *head, int m, int n) { 
        auto dummy = new ListNode(-1);
        dummy->next = head;
        auto pre = dummy;
        for (int i = 0; i < m - 1; i++) {
            pre = pre->next;
        }
        auto cur = pre->next;
        ListNode *next;
        for (int i = 0; i < n - m; i++) {
            next = cur->next;
            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }
        return dummy->next;
    }
    
    // 8 相交链表 LeetCode 8
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *a = headA;
        ListNode *b = headB;
        while ( a != b) {
            a = a == NULL ? headB : a->next;
            b = b == NULL ? headA : b->next;
        }
        return b;
    }
    
    // 9 是否是环形链表
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast != NULL && fast->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast) {
                ListNode *index1 = head;
                ListNode *index2 = fast;
                while (index1 != index2) {
                    index2 = index2->next;
                    index1 = index1->next;
                }
                return  index2;
            }
        }
        return  NULL;
    }
    
    // 10 对链表进行插入排序
    ListNode* inserSort(ListNode *head) {
        if (head == NULL) return NULL;
        auto dummy = new ListNode(-1);
        dummy->next = head;
        auto last = head;
        auto cur = head->next;
        while (cur) {
            if (last->var <= cur->var) {
                last = last->next;
            } else {
                ListNode *pre = dummy;
                while (pre->next->var <= cur->var) {
                    // 找到要插入前的pre指针
                    pre = pre->next;
                }
                // 把cur插入道pre的后面
                last->next = cur->next;
                cur->next = pre->next;
                pre->next = cur;
            }
            cur = last->next;
        }
        return dummy->next;
    }
    
    // 11 递归反转链表
    ListNode *reverseRecurs(ListNode *head) {
        if (head->next == NULL) return head;
        printListNode(head, "head Recurs");
        ListNode *last = reverseRecurs(head->next);
        // 反转指针
        printListNode(head, "head first");
        printListNode(last, "last first");
        head->next->next = head;
        head->next = NULL;
        printListNode(head, "head");
        printListNode(last, "last");
        return last;
    }
    
    // 12 递归反转前m的链表
    
    ListNode *reverseRecursM(ListNode *head, int n) {
        if (head->next == NULL) return head;
        if (n == 1) {
            sucessor = head->next;
            return head;
        }
        ListNode *last = reverseRecursM(head->next, n - 1);
        head->next->next = head;
        head->next = sucessor;
        return last;
    }
    
    ListNode *sucessor = NULL;
    // 13 递归反转m-n 链表
    ListNode *reverseRecursMtoN (ListNode *head, int m, int n) {
        if (head->next == NULL) return head;
        if (n == 1) {
            sucessor = head->next;
            return head;
        }
        ListNode *last = reverseFromMtoN(head, m, n-1);
        head->next->next = head;
        head->next = sucessor;
        return last;
    }
    
    // 14。回文链表
    ListNode* left = NULL;
    bool isPanlinDrome (ListNode* head) {
        left = head;
        return traverse(head);
    }
    // 递归后序遍历链表
    bool traverse (ListNode* head) {
        if (head == nullptr) {
            return true;
        }
        bool res = traverse(head->next);
        res = res && (left->var == head->var);
        left = left->next;
        return res;
    }
    
    
    // 15. k个反转链表
    ListNode* reverseK (ListNode* head, int, k) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode* a = head;
        ListNode* b = head;
        for (int i = 0; i < k; k++) {
            if (b == nullptr) return head;
            b = b->next;
        }
        // 递归前序，
        ListNode* newHead =  reverseKFromN(a, b);
        // 进行分段递归
        a->next = reverseK(b, k);
        return newHead;
    }
    
    // 反转前n个链表
    ListNode* reverseKFromN(ListNode* head, ListNode* end) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        ListNode* next = head;
        while (cur != end) {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
        
    }
    
    // 打印链表的每个节点
    void printListNode (ListNode *head, string tag) {
        cout << tag + "=====" << endl;
        for (ListNode *cur = head; cur ; cur=cur->next) {
            cout << cur->var << "->";
        }
        cout << "\b\b" << endl;
    }
           
};


int main() {
    
//    ListNode *l1 = create_linkedlist({4, 2, 1, 3});
    ListNode *l1 = create_linkedlist({2, 9, 4, 5, 7, 8});
    for (ListNode *cur = l1; cur ; cur=cur->next)
        cout << cur->var << "->";
    cout << "\b\b" << endl;
    Solution s;
    
    
    // 删除倒数第N个节点
//    ListNode *head = s.deleteNthFromEnd(l1, 2);
    
    // 删除有序链表中的重复元素
//    ListNode *head = s.reverseFromMtoN(l1, 2, 5);
    ListNode *head = s.reverseRecursMtoN(l1, 2, 3);
//    cout << head->var << endl;
    for (ListNode *cur = head; cur ; cur=cur->next)
        cout << cur->var << "->";
    cout << "\b\b" << endl;
}
