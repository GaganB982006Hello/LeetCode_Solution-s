'''
You are given two integers num1 and num2 representing an inclusive range [num1, num2].

The waviness of a number is defined as the total count of its peaks and valleys:

A digit is a peak if it is strictly greater than both of its immediate neighbors.
A digit is a valley if it is strictly less than both of its immediate neighbors.
The first and last digits of a number cannot be peaks or valleys.
Any number with fewer than 3 digits has a waviness of 0.
Return the total sum of waviness for all numbers in the range [num1, num2].
 

Example 1:

Input: num1 = 120, num2 = 130

Output: 3

Explanation:

In the range [120, 130]:

120: middle digit 2 is a peak, waviness = 1.
121: middle digit 2 is a peak, waviness = 1.
130: middle digit 3 is a peak, waviness = 1.
All other numbers in the range have a waviness of 0.
Thus, total waviness is 1 + 1 + 1 = 3.

Example 2:

Input: num1 = 198, num2 = 202

Output: 3

Explanation:

In the range [198, 202]:

198: middle digit 9 is a peak, waviness = 1.
201: middle digit 0 is a valley, waviness = 1.
202: middle digit 0 is a valley, waviness = 1.
All other numbers in the range have a waviness of 0.
Thus, total waviness is 1 + 1 + 1 = 3.

Example 3:

Input: num1 = 4848, num2 = 4848

Output: 2

Explanation:

Number 4848: the second digit 8 is a peak, and the third digit 4 is a valley, giving a waviness of 2.

 

Constraints:

1 <= num1 <= num2 <= 1015​​​​​​​
'''

class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        def solve(num: int) -> int:
            if num < 0:
                return 0
            s = str(num)
            memo = {}
            
            def dp(idx, tight, isLz, prev1, prev2):
                if idx == len(s):
                    return (1, 0)
                
                state = (idx, tight, isLz, prev1, prev2)
                if state in memo:
                    return memo[state]
                    
                limit = int(s[idx]) if tight else 9
                tot_count = 0
                tot_sum = 0
                
                for d in range(limit + 1):
                    nxt_tight = tight and (d == limit)
                    
                    if isLz:
                        if d == 0:
                            c, sm = dp(idx + 1, nxt_tight, True, -1, -1)
                            tot_count += c
                            tot_sum += sm
                        else:
                            c, sm = dp(idx + 1, nxt_tight, False, d, -1)
                            tot_count += c
                            tot_sum += sm
                    else:
                        is_wave = 0
                        if prev1 != -1 and prev2 != -1:
                            if (prev1 > prev2 and prev1 > d) or (prev1 < prev2 and prev1 < d):
                                is_wave = 1
                                
                        c, sm = dp(idx + 1, nxt_tight, False, d, prev1)
                        tot_count += c
                        tot_sum += sm + c * is_wave
                        
                memo[state] = (tot_count, tot_sum)
                return memo[state]
                
            return dp(0, True, True, -1, -1)[1]
        
        return solve(num2) - solve(num1 - 1)
