'''
There exists an infinite number line, with its origin at 0 and extending towards the positive x-axis.

You are given a 2D array queries, which contains two types of queries:

For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin. It is guaranteed that there is no obstacle at distance x when the query is asked.
For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note that you do not actually place the block. Queries are separate.
Return a boolean array results, where results[i] is true if you can place the block specified in the ith query of type 2, and false otherwise.

 

Example 1:

Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]

Output: [false,true,true]

Explanation:



For query 0, place an obstacle at x = 2. A block of size at most 2 can be placed before x = 3.

Example 2:

Input: queries = [[1,7],[2,7,6],[1,2],[2,7,5],[2,7,6]]

Output: [true,true,false]

Explanation:



Place an obstacle at x = 7 for query 0. A block of size at most 7 can be placed before x = 7.
Place an obstacle at x = 2 for query 2. Now, a block of size at most 5 can be placed before x = 7, and a block of size at most 2 before x = 2.
 

Constraints:

1 <= queries.length <= 15 * 104
2 <= queries[i].length <= 3
1 <= queries[i][0] <= 2
1 <= x, sz <= min(5 * 104, 3 * queries.length)
The input is generated such that for queries of type 1, no obstacle exists at distance x when the query is asked.
The input is generated such that there is at least one query of type 2.
'''

from sortedcontainers import SortedList

class SegmentTree:
    def __init__(self, size):
        self.n = size
        self.tree = [0] * (4 * size)

    def update(self, node, start, end, idx, val):
        if start == end:
            self.tree[node] = val
            return
        mid = (start + end) // 2
        if start <= idx <= mid:
            self.update(2 * node, start, mid, idx, val)
        else:
            self.update(2 * node + 1, mid + 1, end, idx, val)
        self.tree[node] = max(self.tree[2 * node], self.tree[2 * node + 1])

    def query(self, node, start, end, l, r):
        if r < start or end < l:
            return 0
        if l <= start and end <= r:
            return self.tree[node]
        mid = (start + end) // 2
        p1 = self.query(2 * node, start, mid, l, r)
        p2 = self.query(2 * node + 1, mid + 1, end, l, r)
        return max(p1, p2)

class Solution:
    def getResults(self, queries: list[list[int]]) -> list[bool]:
        # Determine the maximum coordinate limit dynamically
        max_x = min(50000, 3 * len(queries)) + 1
        
        st = SegmentTree(max_x)
        obstacles = SortedList([0, max_x])
        
        # Initially, the obstacle at max_x has a distance of max_x from 0
        st.update(1, 0, max_x - 1, max_x, max_x)
        
        results = []
        
        for q in queries:
            if q[0] == 1:
                x = q[1]
                idx = obstacles.bisect_left(x)
                left = obstacles[idx - 1]
                right = obstacles[idx]
                
                obstacles.add(x)
                st.update(1, 0, max_x - 1, x, x - left)
                st.update(1, 0, max_x - 1, right, right - x)
                
            elif q[0] == 2:
                x, sz = q[1], q[2]
                idx = obstacles.bisect_right(x)
                prev_obstacle = obstacles[idx - 1]
                
                # Check maximum gap before the previous obstacle
                max_gap = st.query(1, 0, max_x - 1, 0, prev_obstacle)
                # Check the remaining tail space up to x
                tail_gap = x - prev_obstacle
                
                results.append(max(max_gap, tail_gap) >= sz)
                
        return results
