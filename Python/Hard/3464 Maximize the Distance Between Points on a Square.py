'''
You are given an integer side, representing the edge length of a square with corners at (0, 0), (0, side), (side, 0), and (side, side) on a Cartesian plane.

You are also given a positive integer k and a 2D integer array points, where points[i] = [xi, yi] represents the coordinate of a point lying on the boundary of the square.

You need to select k elements among points such that the minimum Manhattan distance between any two points is maximized.

Return the maximum possible minimum Manhattan distance between the selected k points.

The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.

 

Example 1:

Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4

Output: 2

Explanation:



Select all four points.

Example 2:

Input: side = 2, points = [[0,0],[1,2],[2,0],[2,2],[2,1]], k = 4

Output: 1

Explanation:



Select the points (0, 0), (2, 0), (2, 2), and (2, 1).

Example 3:

Input: side = 2, points = [[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]], k = 5

Output: 1

Explanation:



Select the points (0, 0), (0, 1), (0, 2), (1, 2), and (2, 2).

 

Constraints:

1 <= side <= 109
4 <= points.length <= min(4 * side, 15 * 103)
points[i] == [xi, yi]
The input is generated such that:
points[i] lies on the boundary of the square.
All points[i] are unique.
4 <= k <= min(25, points.length)
'''

class Solution:
    def maxDistance(self, side: int, points: list[list[int]], k: int) -> int:
        nums = []
        for x, y in points:
            if y == 0: nums.append(x)
            elif x == side: nums.append(side + y)
            elif y == side: nums.append(3 * side - x)
            else: nums.append(3 * side + (side - y))
        
        nums.sort()
        n = len(nums)
        perimeter = 4 * side
        
        def check(mid):
            # We only need to check starting positions in the first interval
            # that could realistically start a valid sequence.
            for i in range(n):
                if nums[i] - nums[0] > perimeter // k: break
                
                count = 1
                curr_idx = i
                last_val = nums[i]
                
                # Use binary search to find the next point >= last_val + mid
                # or just a linear scan if k is small enough.
                for _ in range(k - 1):
                    target = last_val + mid
                    import bisect
                    idx = bisect.bisect_left(nums, target, lo=curr_idx + 1)
                    if idx == n: break
                    last_val = nums[idx]
                    curr_idx = idx
                    count += 1
                
                if count == k and (nums[i] + perimeter - last_val) >= mid:
                    return True
            return False

        low, high = 1, side
        ans = 0
        while low <= high:
            mid = (low + high) // 2
            if check(mid):
                ans = mid
                low = mid + 1
            else:
                high = mid - 1
        return ans
