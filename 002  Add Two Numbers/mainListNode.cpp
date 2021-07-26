#include <iostream>
#include <cstddef>
#include <cstdlib>

using namespace std;

/**
 * 结点
 */
struct ListNode {
    int val; // 结点值
    ListNode *next; // 指向下一个结点地址的指针
    ListNode(int x) : val(x), next(NULL) {}
};

/**
 * 创建链表
 * @param list
 * @return
 */
ListNode *create_linkedlist (std::initializer_list<int> list) {
    auto iter = list.begin();
    ListNode *head = list.size() ? new ListNode(*iter++) : NULL;
    for (ListNode *cur = head; iter != list.end(); cur=cur->next)
        cur->next = new ListNode(*iter++);
    return head;
}

class Solution {
public:
    ListNode *addTwoNumbers (ListNode *li, ListNode *l2) {
        // 创建虚拟结点
        ListNode *dummyHead = new ListNode(0);
        ListNode *cur = dummyHead;
        // 两数之和可能大于10 溢出
        int extra = 0;
        while (li || l2 || extra) {
            int sum = (li ? li->val : 0) + (l2 ? l2->val : 0) + extra;
            extra = sum / 10;
            li = li ? li->next : li;
            l2 = l2 ? l2->next : l2;
            cur->next = new ListNode(sum % 10);
            cur = cur->next;
        }
        return dummyHead->next;
    }
};

int main() {
    ListNode *l1 = create_linkedlist({2, 4, 3});
    ListNode *l2 = create_linkedlist({5, 6, 4});
    for (ListNode *cur = l1; cur ; cur=cur->next)
        cout << cur->val << "->";
    cout << "\b\b" << endl;
    for (ListNode *cur = l2; cur ; cur=cur->next)
        cout << cur->val << "->";
    cout << "\b\b" << endl;

    Solution s;
    ListNode *result = s.addTwoNumbers(l1, l2);
    for (ListNode *cur = result; cur ; cur=cur->next)
        cout << cur->val << "->";
    cout << "\b\b" << endl;

    return 0;
}
