'''
Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.

A shift on s consists of moving the leftmost character of s to the rightmost position.

For example, if s = "abcde", then it will be "bcdea" after one shift.
 

Example 1:

Input: s = "abcde", goal = "cdeab"
Output: true
Example 2:

Input: s = "abcde", goal = "abced"
Output: false
 

Constraints:

1 <= s.length, goal.length <= 100
s and goal consist of lowercase English letters.
'''

class Solution:
    def rotateString(self, s: str, goal: str) -> bool:
        # If lengths aren't equal, s can never become goal
        if len(s) != len(goal):
            return False
        
        # Check if goal is a substring of s + s
        return goal in (s + s)
