/*
You want to build n new buildings in a city. The new buildings will be built in a line and are labeled from 1 to n.

However, there are city restrictions on the heights of the new buildings:

The height of each building must be a non-negative integer.
The height of the first building must be 0.
The height difference between any two adjacent buildings cannot exceed 1.
Additionally, there are city restrictions on the maximum height of specific buildings. These restrictions are given as a 2D integer array restrictions where restrictions[i] = [idi, maxHeighti] indicates that building idi must have a height less than or equal to maxHeighti.

It is guaranteed that each building will appear at most once in restrictions, and building 1 will not be in restrictions.

Return the maximum possible height of the tallest building.

 

Example 1:


Input: n = 5, restrictions = [[2,1],[4,1]]
Output: 2
Explanation: The green area in the image indicates the maximum allowed height for each building.
We can build the buildings with heights [0,1,2,1,2], and the tallest building has a height of 2.
Example 2:


Input: n = 6, restrictions = []
Output: 5
Explanation: The green area in the image indicates the maximum allowed height for each building.
We can build the buildings with heights [0,1,2,3,4,5], and the tallest building has a height of 5.
Example 3:


Input: n = 10, restrictions = [[5,3],[2,5],[7,4],[10,3]]
Output: 5
Explanation: The green area in the image indicates the maximum allowed height for each building.
We can build the buildings with heights [0,1,2,3,3,4,4,5,4,3], and the tallest building has a height of 5.
 

Constraints:

2 <= n <= 109
0 <= restrictions.length <= min(n - 1, 105)
2 <= idi <= n
idi is unique.
0 <= maxHeighti <= 109
*/

import java.util.Arrays;

class Solution {
    public int maxBuilding(int n, int[][] restrictions) {
        int m = restrictions.length;
        // Create a new array to include the fixed restriction for the first building
        int[][] arr = new int[m + 1][2];
        for (int i = 0; i < m; i++) {
            arr[i] = restrictions[i];
        }
        // Building 1 must have a height of 0
        arr[m] = new int[]{1, 0};
        
        // Sort restrictions based on building ID
        Arrays.sort(arr, (a, b) -> Integer.compare(a[0], b[0]));
        
        // Left-to-right pass: cap height based on the left neighbor's limit
        for (int i = 1; i <= m; i++) {
            arr[i][1] = Math.min(arr[i][1], arr[i-1][1] + arr[i][0] - arr[i-1][0]);
        }
        
        // Right-to-left pass: cap height based on the right neighbor's limit
        for (int i = m - 1; i >= 0; i--) {
            arr[i][1] = Math.min(arr[i][1], arr[i+1][1] + arr[i+1][0] - arr[i][0]);
        }
        
        int ans = 0;
        // Find the maximum peak between any two adjacent restrictions
        for (int i = 1; i <= m; i++) {
            int x1 = arr[i-1][0], h1 = arr[i-1][1];
            int x2 = arr[i][0], h2 = arr[i][1];
            // Use long to prevent integer overflow since additions can exceed 2.14 billion
            ans = Math.max(ans, (int)(((long)h1 + h2 + x2 - x1) / 2));
        }
        
        // Check the potential height of the last building 'n' if it's beyond our last restriction
        ans = Math.max(ans, arr[m][1] + (n - arr[m][0]));
        
        return ans;
    }
}
