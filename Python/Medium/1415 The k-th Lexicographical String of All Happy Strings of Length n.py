class Solution:
    def getHappyString(self, n: int, k: int) -> str:
        self.k = k
        self.result = ""
        
        def backtrack(current_path):
            if len(current_path) == n:
                self.k -= 1
                if self.k == 0:
                    self.result = "".join(current_path)
                return
            
            for char in ['a', 'b', 'c']:
                if self.result: return # Found the k-th string
                
                if not current_path or current_path[-1] != char:
                    current_path.append(char)
                    backtrack(current_path)
                    current_path.pop()
        
        backtrack([])
        return self.result
