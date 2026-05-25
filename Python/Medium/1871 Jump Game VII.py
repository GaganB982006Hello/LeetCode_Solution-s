'''
You are given a 0-indexed binary string s and two integers minJump and maxJump. In the beginning, you are standing at index 0, which is equal to '0'. You can move from index i to index j if the following conditions are fulfilled:

i + minJump <= j <= min(i + maxJump, s.length - 1), and
s[j] == '0'.
Return true if you can reach index s.length - 1 in s, or false otherwise.

 

Example 1:

Input: s = "011010", minJump = 2, maxJump = 3
Output: true
Explanation:
In the first step, move from index 0 to index 3. 
In the second step, move from index 3 to index 5.
Example 2:

Input: s = "01101110", minJump = 2, maxJump = 3
Output: false
 

Constraints:

2 <= s.length <= 105
s[i] is either '0' or '1'.
s[0] == '0'
1 <= minJump <= maxJump < s.length
'''

class Solution:
    def canReach(self, s: str, minJump: int, maxJump: int) -> bool:
        n = len(s)
        if s[n - 1] == '1':
            return False
            
        # dp[i] will be True if index i is reachable
        dp = [False] * n
        dp[0] = True
        
        reachable_count = 0
        
        for i in range(1, n):
            # Add the new index that enters the sliding window from the right
            if i >= minJump and dp[i - minJump]:
                reachable_count += 1
                
            # Remove the index that exits the sliding window from the left
            if i > maxJump and dp[i - maxJump - 1]:
                reachable_count -= 1
                
            # If s[i] is '0' and there is at least one reachable index in the window
            if s[i] == '0' and reachable_count > 0:
                dp[i] = True
                
        return dp[n - 1]
