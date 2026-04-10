'''
You are given an integer array nums.

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

1 <= n == nums.length <= 100
1 <= nums[i] <= n
'''

from collections import defaultdict

class Solution:
    def minimumDistance(self, nums: list[int]) -> int:
        # Dictionary to store a list of indices for each number
        index_map = defaultdict(list)
        min_dist = float('inf')
        
        for i, num in enumerate(nums):
            # Add current index to the list for this number
            index_map[num].append(i)
            
            # If we have at least 3 occurrences, calculate the distance
            if len(index_map[num]) >= 3:
                # The triplet indices are (i, j, k)
                # k is the current index: index_map[num][-1]
                # i is the index from two occurrences ago: index_map[num][-3]
                
                # Formula: (j-i) + (k-j) + (k-i) simplifies to 2 * (k - i)
                span = index_map[num][-1] - index_map[num][-3]
                current_total_dist = 2 * span
                
                if current_total_dist < min_dist:
                    min_dist = current_total_dist
                    
        # Return -1 if no triplet was found, otherwise the minimum distance
        return min_dist if min_dist != float('inf') else -1
