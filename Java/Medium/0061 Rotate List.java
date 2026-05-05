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

class Solution {
    public ListNode rotateRight(ListNode head, int k) {
        if (head == null || head.next == null || k == 0) return head;

        // 1. Find the length and the old tail
        ListNode old_tail = head;
        int n = 1;
        while (old_tail.next != null) {
            old_tail = old_tail.next;
            n++;
        }

        // 2. Close the linked list into a ring
        old_tail.next = head;

        // 3. Find new tail: (n - k % n - 1)th node
        // and new head: (n - k % n)th node
        ListNode new_tail = head;
        for (int i = 0; i < n - k % n - 1; i++) {
            new_tail = new_tail.next;
        }
        ListNode new_head = new_tail.next;

        // 4. Break the ring
        new_tail.next = null;

        return new_head;
    }
}
