import math
from typing import List

class Solution:
    def minNumberOfSeconds(self, mountainHeight: int, workerTimes: List[int]) -> int:
        def get_reduced_height(m: int) -> int:
            total_height = 0
            for w in workerTimes:
                # math.isqrt prevents precision issues with very large numbers
                total_height += (-1 + math.isqrt(1 + 8 * m // w)) // 2
            return total_height
        
        l = 1
        r = min(workerTimes) * mountainHeight * (mountainHeight + 1) // 2
        
        while l < r:
            mid = (l + r) // 2
            if get_reduced_height(mid) < mountainHeight:
                l = mid + 1
            else:
                r = mid
                
        return l
