/*
Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.

Notice that you can not jump outside of the array at any time.

 

Example 1:

Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation: 
All possible ways to reach at index 3 with value 0 are: 
index 5 -> index 4 -> index 1 -> index 3 
index 5 -> index 6 -> index 4 -> index 1 -> index 3 
Example 2:

Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true 
Explanation: 
One possible way to reach at index 3 with value 0 is: 
index 0 -> index 4 -> index 1 -> index 3
Example 3:

Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no way to reach at index 1 with value 0.
 

Constraints:

1 <= arr.length <= 5 * 104
0 <= arr[i] < arr.length
0 <= start < arr.length
*/

class Solution {
    public boolean canReach(int[] arr, int start) {
        // Base cases: out of bounds or already visited
        if (start < 0 || start >= arr.length || arr[start] < 0) {
            return false;
        }
        
        // Target found
        if (arr[start] == 0) {
            return true;
        }
        
        // Mark as visited by flipping the sign
        int jump = arr[start];
        arr[start] = -arr[start];
        
        // Explore both directions
        return canReach(arr, start + jump) || canReach(arr, start - jump);
    }
}
