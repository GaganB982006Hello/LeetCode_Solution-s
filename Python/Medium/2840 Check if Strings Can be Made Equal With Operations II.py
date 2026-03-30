class Solution:
    def checkStrings(self, s1: str, s2: str) -> bool:
        # Check if even-indexed chars match and odd-indexed chars match
        return (sorted(s1[0::2]) == sorted(s2[0::2]) ands sorted(s1[1::2]) == sorted(s2[1::2]))
