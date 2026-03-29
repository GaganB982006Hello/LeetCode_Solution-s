class Solution:
    def findTheString(self, lcp: List[List[int]]) -> str:
        n = len(lcp)
        s = [0] * n
        char_val = 1
        
        for i in range(n):
            if s[i] > 0: continue
            if char_val > 26: return ""
            for j in range(i, n):
                if lcp[i][j] > 0:
                    s[j] = char_val
            char_val += 1
            
        for i in range(n - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                expected = 0
                if s[i] == s[j]:
                    expected = 1 + (lcp[i+1][j+1] if i < n-1 and j < n-1 else 0)
                if lcp[i][j] != expected:
                    return ""
                    
        return "".join(chr(ord('a') + v - 1) for v in s)
