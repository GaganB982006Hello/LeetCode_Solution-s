'''
Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.

A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.

Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.

Return true if any cycle of the same value exists in grid, otherwise, return false.

 

Example 1:



Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
Output: true
Explanation: There are two valid cycles shown in different colors in the image below:

Example 2:



Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
Output: true
Explanation: There is only one valid cycle highlighted in the image below:

'''

class Solution:
    def containsCycle(self, grid: List[List[str]]) -> bool:
        rows, cols = len(grid), len(grid[0])
        visited = set()

        def dfs(r, c, pr, pc, char):
            visited.add((r, c))
            
            for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nr, nc = r + dr, c + dc
                
                # Stay within bounds and match the character
                if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == char:
                    # If we hit a visited cell that isn't our parent, it's a cycle
                    if (nr, nc) in visited:
                        if (nr, nc) != (pr, pc):
                            return True
                    else:
                        if dfs(nr, nc, r, c, char):
                            return True
            return False

        for r in range(rows):
            for c in range(cols):
                if (r, c) not in visited:
                    if dfs(r, c, -1, -1, grid[r][c]):
                        return True
        return False
