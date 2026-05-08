/*
You are given an integer array nums of length n.

You start at index 0, and your goal is to reach index n - 1.

From any index i, you may perform one of the following operations:

Adjacent Step: Jump to index i + 1 or i - 1, if the index is within bounds.
Prime Teleportation: If nums[i] is a prime number p, you may instantly jump to any index j != i such that nums[j] % p == 0.
Return the minimum number of jumps required to reach index n - 1.

 

Example 1:

Input: nums = [1,2,4,6]

Output: 2

Explanation:

One optimal sequence of jumps is:

Start at index i = 0. Take an adjacent step to index 1.
At index i = 1, nums[1] = 2 is a prime number. Therefore, we teleport to index i = 3 as nums[3] = 6 is divisible by 2.
Thus, the answer is 2.

Example 2:

Input: nums = [2,3,4,7,9]

Output: 2

Explanation:

One optimal sequence of jumps is:

Start at index i = 0. Take an adjacent step to index i = 1.
At index i = 1, nums[1] = 3 is a prime number. Therefore, we teleport to index i = 4 since nums[4] = 9 is divisible by 3.
Thus, the answer is 2.

Example 3:

Input: nums = [4,6,5,8]

Output: 3

Explanation:

Since no teleportation is possible, we move through 0 → 1 → 2 → 3. Thus, the answer is 3.
 

Constraints:

1 <= n == nums.length <= 105
1 <= nums[i] <= 106
*/
from collections import deque

class Solution:
    # Precompute Sieve of Eratosthenes up to 10^6
    MAX_VAL = 1000001
    spf = list(range(MAX_VAL))
    for i in range(2, int(MAX_VAL**0.5) + 1):
        if spf[i] == i:
            for j in range(i*i, MAX_VAL, i):
                if spf[j] == j:
                    spf[j] = i

    def minJumps(self, nums: list[int]) -> int:
        n = len(nums)
        if n == 1: return 0
        
        # Map each prime to indices where nums[j] % p == 0
        prime_to_indices = {}
        for i, val in enumerate(nums):
            temp = val
            while temp > 1:
                p = self.spf[temp]
                if p not in prime_to_indices:
                    prime_to_indices[p] = []
                prime_to_indices[p].append(i)
                while temp % p == 0:
                    temp //= p
        
        queue = deque([0])
        visited_idx = [False] * n
        visited_idx[0] = True
        visited_primes = set()
        jumps = 0
        
        while queue:
            for _ in range(len(queue)):
                curr_idx = queue.popleft()
                if curr_idx == n - 1:
                    return jumps
                
                # 1. Adjacent Steps
                for neighbor in [curr_idx - 1, curr_idx + 1]:
                    if 0 <= neighbor < n and not visited_idx[neighbor]:
                        visited_idx[neighbor] = True
                        queue.append(neighbor)
                
                # 2. Prime Teleportation (Only if nums[curr_idx] is prime)
                val = nums[curr_idx]
                if val > 1 and self.spf[val] == val:
                    if val not in visited_primes:
                        visited_primes.add(val)
                        if val in prime_to_indices:
                            for next_idx in prime_to_indices[val]:
                                if not visited_idx[next_idx]:
                                    visited_idx[next_idx] = True
                                    queue.append(next_idx)
                            # Efficiency: Clear the bucket after use
                            del prime_to_indices[val]
            jumps += 1
            
        return -1
