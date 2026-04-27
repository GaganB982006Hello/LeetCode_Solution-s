'''
You are given an m x n grid. Each cell of grid represents a street. The street of grid[i][j] can be:

1 which means a street connecting the left cell and the right cell.
2 which means a street connecting the upper cell and the lower cell.
3 which means a street connecting the left cell and the lower cell.
4 which means a street connecting the right cell and the lower cell.
5 which means a street connecting the left cell and the upper cell.
6 which means a street connecting the right cell and the upper cell.

You will initially start at the street of the upper-left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.

Notice that you are not allowed to change any street.

Return true if there is a valid path in the grid or false otherwise.

 

Example 1:


Input: grid = [[2,4,3],[6,5,2]]
Output: true
Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
Example 2:


Input: grid = [[1,2,1],[1,2,1]]
Output: false
Explanation: As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get stuck at cell (0, 0)
Example 3:

Input: grid = [[1,1,2]]
Output: false
Explanation: You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
1 <= grid[i][j] <= 6
'''

from collections import deque

class Solution:
    def hasValidPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        # directions: 0: up, 1: down, 2: left, 3: right
        directions = {
            1: [(0, -2), (0, 3)],
            2: [(-1, 0), (1, 1)],
            3: [(0, -2), (1, 1)],
            4: [(0, 3), (1, 1)],
            5: [(0, -2), (-1, 0)],
            6: [(0, 3), (-1, 0)]
        }
        
        # Mapping which directions a street connects to
        # (row_offset, col_offset): direction_index
        # 0: Up, 1: Down, 2: Left, 3: Right
        pipes = {
            1: {2, 3}, 2: {0, 1}, 3: {2, 1},
            4: {3, 1}, 5: {2, 0}, 6: {3, 0}
        }
        
        # Helper to check if two cells can connect
        def can_connect(r1, c1, r2, c2):
            dr, dc = r2 - r1, c2 - c1
            # Determine which direction we are moving from (r1, c1)
            if dr == -1: d = 0 # Up
            elif dr == 1: d = 1 # Down
            elif dr == 0 and dc == -1: d = 2 # Left
            else: d = 3 # Right
            
            # (r1,c1) must have an exit in direction 'd'
            # (r2,c2) must have an entry from the opposite of 'd'
            opposite = {0: 1, 1: 0, 2: 3, 3: 2}
            return d in pipes[grid[r1][c1]] and opposite[d] in pipes[grid[r2][c2]]

        q = deque([(0, 0)])
        visited = {(0, 0)}
        
        while q:
            r, c = q.popleft()
            if r == m - 1 and c == n - 1:
                return True
            
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and (nr, nc) not in visited:
                    if can_connect(r, c, nr, nc):
                        visited.add((nr, nc))
                        q.append((nr, nc))
        return False
