'''
You are given a string s consisting of lowercase English letters and the special characters: '*', '#', and '%'.

You are also given an integer k.

Build a new string result by processing s according to the following rules from left to right:

If the letter is a lowercase English letter append it to result.
A '*' removes the last character from result, if it exists.
A '#' duplicates the current result and appends it to itself.
A '%' reverses the current result.
Return the kth character of the final string result. If k is out of the bounds of result, return '.'.

 

Example 1:

Input: s = "a#b%*", k = 1

Output: "a"

Explanation:

i	s[i]	Operation	Current result
0	'a'	Append 'a'	"a"
1	'#'	Duplicate result	"aa"
2	'b'	Append 'b'	"aab"
3	'%'	Reverse result	"baa"
4	'*'	Remove the last character	"ba"
The final result is "ba". The character at index k = 1 is 'a'.

Example 2:

Input: s = "cd%#*#", k = 3

Output: "d"

Explanation:

i	s[i]	Operation	Current result
0	'c'	Append 'c'	"c"
1	'd'	Append 'd'	"cd"
2	'%'	Reverse result	"dc"
3	'#'	Duplicate result	"dcdc"
4	'*'	Remove the last character	"dcd"
5	'#'	Duplicate result	"dcddcd"
The final result is "dcddcd". The character at index k = 3 is 'd'.

Example 3:

Input: s = "z*#", k = 0

Output: "."

Explanation:

i	s[i]	Operation	Current result
0	'z'	Append 'z'	"z"
1	'*'	Remove the last character	""
2	'#'	Duplicate the string	""
The final result is "". Since index k = 0 is out of bounds, the output is '.'.

 

Constraints:

1 <= s.length <= 105
s consists of only lowercase English letters and special characters '*', '#', and '%'.
0 <= k <= 1015
The length of result after processing s will not exceed 1015.
'''

class Solution:
    def processStr(self, s: str, k: int) -> str:
        n = len(s)
        lengths = [0] * n
        curr_len = 0
        
        # Forward pass: Process the ENTIRE string
        for i, ch in enumerate(s):
            if ch.isalpha():
                curr_len += 1
            elif ch == '*':
                if curr_len > 0:
                    curr_len -= 1
            elif ch == '#':
                curr_len *= 2
                
            lengths[i] = curr_len
            
        if k >= curr_len:
            return '.'
            
        # Backward pass
        for i in range(n - 1, -1, -1):
            ch = s[i]
            prev_len = lengths[i-1] if i > 0 else 0
            
            if ch.isalpha():
                if k == curr_len - 1:
                    return ch
                curr_len = prev_len
            elif ch == '*':
                curr_len = prev_len
            elif ch == '#':
                curr_len = prev_len
                if k >= curr_len:
                    k %= curr_len
            elif ch == '%':
                k = curr_len - 1 - k
                curr_len = prev_len
                
        return '.'
