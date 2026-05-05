'''
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
'''

class Solution:
    def rotateRight(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        if not head or not head.next or k == 0:
            return head
        
        # 1. Compute length and find old tail
        old_tail = head
        n = 1
        while old_tail.next:
            old_tail = old_tail.next
            n += 1
        
        # 2. Close the loop
        old_tail.next = head
        
        # 3. Find new tail (n - k % n - 1) steps from head
        new_tail = head
        for _ in range(n - (k % n) - 1):
            new_tail = new_tail.next
        
        new_head = new_tail.next
        
        # 4. Break the loop
        new_tail.next = None
        
        return new_head
