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

1 <= n == nums.length <= 105
1 <= nums[i] <= n
'''

class Solution:
    def minimumDistance(self, nums: list[int]) -> int:
        # dict to store: {value: [second_last_index, last_index]}
        history = {}
        min_dist = float('inf')
        found = False

        for current_idx, val in enumerate(nums):
            if val in history:
                prev_indices = history[val]
                
                # If we have seen this value at least twice before
                if prev_indices[0] != -1:
                    # distance = 2 * (current_index - oldest_index_of_the_triplet)
                    dist = 2 * (current_idx - prev_indices[0])
                    if dist < min_dist:
                        min_dist = dist
                        found = True
                
                # Update history: shift last to second_last, current to last
                history[val] = [prev_indices[1], current_idx]
            else:
                # First time seeing this value
                history[val] = [-1, current_idx]

        return min_dist if found else -1
