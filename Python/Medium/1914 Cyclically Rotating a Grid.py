'''
You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.

The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:



A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An example rotation is shown below:


Return the matrix after applying k cyclic rotations to it.

 

Example 1:


Input: grid = [[40,10],[30,20]], k = 1
Output: [[10,20],[40,30]]
Explanation: The figures above represent the grid at every state.
Example 2:


Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], k = 2
Output: [[3,4,8,12],[2,11,10,16],[1,7,6,15],[5,9,13,14]]
Explanation: The figures above represent the grid at every state.
 

Constraints:

m == grid.length
n == grid[i].length
2 <= m, n <= 50
Both m and n are even integers.
1 <= grid[i][j] <= 5000
1 <= k <= 109
'''
class Solution:
    def rotateGrid(self, grid: List[List[int]], k: int) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        layers = min(m, n) // 2
        
        for l in range(layers):
            elements = []
            # Top row
            for j in range(l, n - 1 - l): elements.append(grid[l][j])
            # Right column
            for i in range(l, m - 1 - l): elements.append(grid[i][n - 1 - l])
            # Bottom row
            for j in range(n - 1 - l, l, -1): elements.append(grid[m - 1 - l][j])
            # Left column
            for i in range(m - 1 - l, l, -1): elements.append(grid[i][l])
            
            # Rotate
            net_k = k % len(elements)
            rotated = elements[net_k:] + elements[:net_k]
            
            # Fill back
            idx = 0
            for j in range(l, n - 1 - l): 
                grid[l][j] = rotated[idx]; idx += 1
            for i in range(l, m - 1 - l): 
                grid[i][n - 1 - l] = rotated[idx]; idx += 1
            for j in range(n - 1 - l, l, -1): 
                grid[m - 1 - l][j] = rotated[idx]; idx += 1
            for i in range(m - 1 - l, l, -1): 
                grid[i][l] = rotated[idx]; idx += 1
                
        return grid
