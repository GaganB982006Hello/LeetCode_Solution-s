'''
You are given an m x n binary matrix grid and an integer health.

You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1).

You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive.

Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1.

Return true if you can reach the final cell with a health value of 1 or more, and false otherwise.

 

Example 1:

Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1

Output: true

Explanation:

The final cell can be reached safely by walking along the gray cells below.


Example 2:

Input: grid = [[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]], health = 3

Output: false

Explanation:

A minimum of 4 health points is needed to reach the final cell safely.


Example 3:

Input: grid = [[1,1,1],[1,0,1],[1,1,1]], health = 5

Output: true

Explanation:

The final cell can be reached safely by walking along the gray cells below.



Any path that does not go through the cell (1, 1) is unsafe since your health will drop to 0 when reaching the final cell.

 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
2 <= m * n
1 <= health <= m + n
grid[i][j] is either 0 or 1.
'''

from collections import deque
from typing import List

class Solution:
    def findSafeWalk(self, grid: List[List[int]], health: int) -> bool:
        m, n = len(grid), len(grid[0])
        
        # Track minimum health lost to reach any given cell
        dist = [[float('inf')] * n for _ in range(m)]
        dist[0][0] = grid[0][0]
        
        q = deque([(0, 0)])
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        while q:
            x, y = q.popleft()
            
            # Short-circuit if we pull the target cell off the queue
            if x == m - 1 and y == n - 1:
                break
                
            for dx, dy in dirs:
                nx, ny = x + dx, y + dy
                
                if 0 <= nx < m and 0 <= ny < n:
                    cost = grid[nx][ny]
                    
                    # If we found a safer way to this neighbor cell
                    if dist[x][y] + cost < dist[nx][ny]:
                        dist[nx][ny] = dist[x][y] + cost
                        
                        if cost == 0:
                            q.appendleft((nx, ny))
                        else:
                            q.append((nx, ny))
                            
        return (health - dist[-1][-1]) > 0
