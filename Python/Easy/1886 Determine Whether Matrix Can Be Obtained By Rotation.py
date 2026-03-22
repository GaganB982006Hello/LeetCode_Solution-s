class Solution:
    def findRotation(self, mat: list[list[int]], target: list[list[int]]) -> bool:
        n = len(mat)
        
        # Assume all 4 possible rotations could be valid initially
        deg0 = deg90 = deg180 = deg270 = True
        
        for i in range(n):
            for j in range(n):
                # Check 0 degrees (no rotation)
                if mat[i][j] != target[i][j]:
                    deg0 = False
                
                # Check 90 degrees clockwise
                if mat[i][j] != target[j][n - 1 - i]:
                    deg90 = False
                
                # Check 180 degrees
                if mat[i][j] != target[n - 1 - i][n - 1 - j]:
                    deg180 = False
                
                # Check 270 degrees clockwise
                if mat[i][j] != target[n - 1 - j][i]:
                    deg270 = False
                    
        # If any rotation remains True, it's a valid match
        return deg0 or deg90 or deg180 or deg270
