/*You are given an integer array nums.

A tuple (i, j, k) of 3 distinct indices is good if nums[i] == nums[j] == nums[k].

The distance of a good tuple is abs(i - j) + abs(j - k) + abs(k - i), where abs(x) denotes the absolute value of x.

Return an integer denoting the minimum possible distance of a good tuple. If no good tuples exist, return -1.

 

Example 1:

Input: nums = [1,2,1,1,3]

Output: 6

Explanation:

The minimum distance is achieved by the good tuple (0, 2, 3).

(0, 2, 3) is a good tuple because nums[0] == nums[2] == nums[3] == 1. Its distance is abs(0 - 2) + abs(2 - 3) + abs(3 - 0) = 2 + 1 + 3 = 6.

Example 2:

Input: nums = [1,1,2,3,2,1,2]

Output: 8

Explanation:

The minimum distance is achieved by the good tuple (2, 4, 6).

(2, 4, 6) is a good tuple because nums[2] == nums[4] == nums[6] == 2. Its distance is abs(2 - 4) + abs(4 - 6) + abs(6 - 2) = 2 + 2 + 4 = 8.

Example 3:

Input: nums = [1]

Output: -1

Explanation:

There are no good tuples. Therefore, the answer is -1.

 

Constraints:

1 <= n == nums.length <= 105
1 <= nums[i] <= n*/

import java.util.*;

class Solution {
    public int minimumDistance(int[] nums) {
        // Map to store value -> list of indices where it appears
        Map<Integer, List<Integer>> indexMap = new HashMap<>();
        
        for (int i = 0; i < nums.length; i++) {
            indexMap.computeIfAbsent(nums[i], k -> new ArrayList<>()).add(i);
        }
        
        long minDistance = Long.MAX_VALUE;
        boolean found = false;
        
        for (List<Integer> indices : indexMap.values()) {
            // A "good tuple" requires at least 3 occurrences
            if (indices.size() < 3) continue;
            
            // Check every three consecutive indices
            for (int i = 0; i <= indices.size() - 3; i++) {
                int first = indices.get(i);
                int third = indices.get(i + 2);
                
                // Formula: 2 * (max_index - min_index)
                long currentDist = 2L * (third - first);
                minDistance = Math.min(minDistance, currentDist);
                found = true;
            }
        }
        
        return found ? (int) minDistance : -1;
    }
}

import java.util.*;

class Solution {
    public int minimumDistance(int[] nums) {
        // Map to store value -> list of indices where it appears
        Map<Integer, List<Integer>> indexMap = new HashMap<>();
        
        for (int i = 0; i < nums.length; i++) {
            indexMap.computeIfAbsent(nums[i], k -> new ArrayList<>()).add(i);
        }
        
        long minDistance = Long.MAX_VALUE;
        boolean found = false;
        
        for (List<Integer> indices : indexMap.values()) {
            // A "good tuple" requires at least 3 occurrences
            if (indices.size() < 3) continue;
            
            // Check every three consecutive indices
            for (int i = 0; i <= indices.size() - 3; i++) {
                int first = indices.get(i);
                int third = indices.get(i + 2);
                
                // Formula: 2 * (max_index - min_index)
                long currentDist = 2L * (third - first);
                minDistance = Math.min(minDistance, currentDist);
                found = true;
            }
        }
        
        return found ? (int) minDistance : -1;
    }
}
