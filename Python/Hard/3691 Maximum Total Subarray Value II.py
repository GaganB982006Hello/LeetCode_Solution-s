'''
You are given an integer array nums of length n and an integer k.

You must select exactly k distinct non-empty subarrays nums[l..r] of nums. Subarrays may overlap, but the exact same subarray (same l and r) cannot be chosen more than once.

The value of a subarray nums[l..r] is defined as: max(nums[l..r]) - min(nums[l..r]).

The total value is the sum of the values of all chosen subarrays.

Return the maximum possible total value you can achieve.

 

Example 1:

Input: nums = [1,3,2], k = 2

Output: 4

Explanation:

One optimal approach is:

Choose nums[0..1] = [1, 3]. The maximum is 3 and the minimum is 1, giving a value of 3 - 1 = 2.
Choose nums[0..2] = [1, 3, 2]. The maximum is still 3 and the minimum is still 1, so the value is also 3 - 1 = 2.
Adding these gives 2 + 2 = 4.

Example 2:

Input: nums = [4,2,5,1], k = 3

Output: 12

Explanation:

One optimal approach is:

Choose nums[0..3] = [4, 2, 5, 1]. The maximum is 5 and the minimum is 1, giving a value of 5 - 1 = 4.
Choose nums[1..3] = [2, 5, 1]. The maximum is 5 and the minimum is 1, so the value is also 4.
Choose nums[2..3] = [5, 1]. The maximum is 5 and the minimum is 1, so the value is again 4.
Adding these gives 4 + 4 + 4 = 12.

 

Constraints:

1 <= n == nums.length <= 5 * 10​​​​​​​4
0 <= nums[i] <= 109
1 <= k <= min(105, n * (n + 1) / 2)
'''

import math
import heapq

class Solution:
    def maxTotalValue(self, nums: list[int], k: int) -> int:
        n = len(nums)
        log = math.floor(math.log2(n)) + 1
        max_st = [[0] * log for _ in range(n)]
        min_st = [[0] * log for _ in range(n)]

        # Initialize sparse tables
        for i in range(n):
            max_st[i][0] = nums[i]
            min_st[i][0] = nums[i]

        # Build sparse tables
        for j in range(1, log):
            for i in range(n - (1 << j) + 1):
                max_st[i][j] = max(max_st[i][j - 1], max_st[i + (1 << (j - 1))][j - 1])
                min_st[i][j] = min(min_st[i][j - 1], min_st[i + (1 << (j - 1))][j - 1])

        def get_val(l, r):
            length = r - l + 1
            j = math.floor(math.log2(length))
            max_val = max(max_st[l][j], max_st[r - (1 << j) + 1][j])
            min_val = min(min_st[l][j], min_st[r - (1 << j) + 1][j])
            return max_val - min_val

        # Python's heapq is a min-heap, so we invert the value to use it as a max-heap
        pq = []
        for i in range(n):
            heapq.heappush(pq, (-get_val(i, n - 1), i, n - 1))

        total = 0
        for _ in range(k):
            if not pq: 
                break
            
            val, l, r = heapq.heappop(pq)
            total += -val  # revert back to positive
            
            if r > l:
                heapq.heappush(pq, (-get_val(l, r - 1), l, r - 1))

        return total
