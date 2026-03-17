class Solution:
    def largestSubmatrix(self, matrix: List[List[int]]) -> int:
        m, n = len(matrix), len(matrix[0])
        max_area = 0
        
        # Step 1: Accumulate heights downwards
        for r in range(1, m):
            for c in range(n):
                if matrix[r][c] == 1:
                    matrix[r][c] += matrix[r-1][c]
        
        # Step 2: Sort heights in each row and find max area
        for r in range(m):
            # Sorting in descending order makes it easier to track width
            row = sorted(matrix[r], reverse=True)
            for i in range(n):
                height = row[i]
                width = i + 1
                max_area = max(max_area, height * width)
                
        return max_area
