'''
You are given an integer array nums.

From any index i, you can jump to another index j under the following rules:

Jump to index j where j > i is allowed only if nums[j] < nums[i].
Jump to index j where j < i is allowed only if nums[j] > nums[i].
For each index i, find the maximum value in nums that can be reached by following any sequence of valid jumps starting at i.

Return an array ans where ans[i] is the maximum value reachable starting from index i.

 

Example 1:

Input: nums = [2,1,3]

Output: [2,2,3]

Explanation:

For i = 0: No jump increases the value.
For i = 1: Jump to j = 0 as nums[j] = 2 is greater than nums[i].
For i = 2: Since nums[2] = 3 is the maximum value in nums, no jump increases the value.
Thus, ans = [2, 2, 3].

Example 2:

Input: nums = [2,3,1]

Output: [3,3,3]

Explanation:

For i = 0: Jump forward to j = 2 as nums[j] = 1 is less than nums[i] = 2, then from i = 2 jump to j = 1 as nums[j] = 3 is greater than nums[2].
For i = 1: Since nums[1] = 3 is the maximum value in nums, no jump increases the value.
For i = 2: Jump to j = 1 as nums[j] = 3 is greater than nums[2] = 1.
Thus, ans = [3, 3, 3].

 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
'''

class Solution:
    def maxValue(self, nums: List[int]) -> List[int]:
        n = len(nums)
        prefix_max = [0] * n
        suffix_min = [0] * n
        
        curr_max = 0
        for i in range(n):
            curr_max = max(curr_max, nums[i])
            prefix_max[i] = curr_max
            
        curr_min = float('inf')
        for i in range(n - 1, -1, -1):
            curr_min = min(curr_min, nums[i])
            suffix_min[i] = curr_min
            
        ans = [0] * n
        l = 0
        while l < n:
            r = l
            comp_max = nums[l]
            while r + 1 < n and prefix_max[r] > suffix_min[r + 1]:
                r += 1
                comp_max = max(comp_max, nums[r])
            
            val = max(comp_max, prefix_max[r])
            for i in range(l, r + 1):
                ans[i] = val
            l = r + 1
        return ans
