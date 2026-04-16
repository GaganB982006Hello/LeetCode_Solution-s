'''
You are given a circular array nums and an array queries.

For each query i, you have to find the following:

The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.
Return an array answer of the same size as queries, where answer[i] represents the result for query i.

 

Example 1:

Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]

Output: [2,-1,3]

Explanation:

Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).
Example 2:

Input: nums = [1,2,3,4], queries = [0,1,2,3]

Output: [-1,-1,-1,-1]

Explanation:

Each value in nums is unique, so no index shares the same value as the queried element. This results in -1 for all queries.

 

Constraints:

1 <= queries.length <= nums.length <= 105
1 <= nums[i] <= 106
0 <= queries[i] < nums.length
'''

from bisect import bisect_left

class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        n = len(nums)
        # Group indices by their values
        pos_map = {}
        for i, val in enumerate(nums):
            if val not in pos_map:
                pos_map[val] = []
            pos_map[val].append(i)
            
        ans = []
        for q_idx in queries:
            val = nums[q_idx]
            indices = pos_map[val]
            
            # If the number appears only once, there's no other equal element
            if len(indices) < 2:
                ans.append(-1)
                continue
            
            # Find the position of the current index in the sorted list
            idx_in_list = bisect_left(indices, q_idx)
            m = len(indices)
            
            # Circular neighbors: left (prev) and right (next)
            prev_idx = indices[(idx_in_list - 1) % m]
            next_idx = indices[(idx_in_list + 1) % m]
            
            # Distance formula for circular array: min(|i-j|, n - |i-j|)
            def get_circular_dist(i, j):
                diff = abs(i - j)
                return min(diff, n - diff)
            
            ans.append(min(get_circular_dist(q_idx, prev_idx), 
                           get_circular_dist(q_idx, next_idx)))
            
        return ans
