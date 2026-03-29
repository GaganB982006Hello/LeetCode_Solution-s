class Solution:
    def canBeEqual(self, s1: str, s2: str) -> bool:
        # Check if characters at indices 0 and 2 can be matched
        even_ok = sorted(s1[0] + s1[2]) == sorted(s2[0] + s2[2])
        # Check if characters at indices 1 and 3 can be matched
        odd_ok = sorted(s1[1] + s1[3]) == sorted(s2[1] + s2[3])
        
        return even_ok and odd_ok
