/*
/**
 * Definition for singly-linked list.
 * public class ListNode {
 * int val;
 * ListNode next;
 * ListNode() {}
 * ListNode(int val) { this.val = val; }
 * ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode deleteMiddle(ListNode head) {
        // Base case: If the list is empty or has only one node
        if (head == null || head.next == null) {
            return null;
        }
        
        ListNode slow = head;
        // Start fast pointer one step ahead so slow stops right before the middle
        ListNode fast = head.next.next;
        
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        
        // Delete the middle node by skipping it
        slow.next = slow.next.next;
        
        return head;
    }
}
*/

/**
 * Definition for singly-linked list.
 * public class ListNode {
 * int val;
 * ListNode next;
 * ListNode() {}
 * ListNode(int val) { this.val = val; }
 * ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode deleteMiddle(ListNode head) {
        // Base case: If the list is empty or has only one node
        if (head == null || head.next == null) {
            return null;
        }
        
        ListNode slow = head;
        // Start fast pointer one step ahead so slow stops right before the middle
        ListNode fast = head.next.next;
        
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        
        // Delete the middle node by skipping it
        slow.next = slow.next.next;
        
        return head;
    }
}
