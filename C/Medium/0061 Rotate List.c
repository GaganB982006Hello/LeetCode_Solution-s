/*
Given the head of a linked list, rotate the list to the right by k places.

 

Example 1:


Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]
Example 2:


Input: head = [0,1,2], k = 4
Output: [2,0,1]
 

Constraints:

The number of nodes in the list is in the range [0, 500].
-100 <= Node.val <= 100
0 <= k <= 2 * 109
  */

struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (!head || !head->next || k == 0) return head;

    // 1. Find length and old tail
    struct ListNode* old_tail = head;
    int n = 1;
    while (old_tail->next) {
        old_tail = old_tail->next;
        n++;
    }

    // 2. Close the ring
    old_tail->next = head;

    // 3. Find new tail and new head
    struct ListNode* new_tail = head;
    k = k % n;
    for (int i = 0; i < n - k - 1; i++) {
        new_tail = new_tail->next;
    }
    
    struct ListNode* new_head = new_tail->next;

    // 4. Break the ring
    new_tail->next = NULL;

    return new_head;
}
