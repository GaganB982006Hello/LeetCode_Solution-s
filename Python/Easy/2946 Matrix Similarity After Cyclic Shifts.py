class Solution:
    def areSimilar(self, mat: List[List[int]], k: int) -> bool:
        n = len(mat[0])
        # After k shifts, the row must be equal to its original state.
        # This is only true if every element matches the element k positions away.
        for row in mat:
            for j in range(n):
                if row[j] != row[(j + k) % n]:
                    return False
        return True
