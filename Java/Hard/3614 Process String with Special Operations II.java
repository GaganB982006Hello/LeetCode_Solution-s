/*
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
*/

class Solution {
    public char processStr(String s, long k) {
        int n = s.length();
        long[] lengths = new long[n];
        long currLen = 0;
        
        // Forward pass: Process the ENTIRE string. No early break.
        for (int i = 0; i < n; i++) {
            char ch = s.charAt(i);
            if (Character.isLetter(ch)) {
                currLen++;
            } else if (ch == '*') {
                if (currLen > 0) currLen--;
            } else if (ch == '#') {
                currLen *= 2;
            } // '%' doesn't change length
            
            lengths[i] = currLen;
        }
        
        if (k >= currLen) {
            return '.';
        }
        
        // Backward pass
        for (int i = n - 1; i >= 0; i--) {
            char ch = s.charAt(i);
            long prevLen = (i > 0) ? lengths[i - 1] : 0;
            
            if (Character.isLetter(ch)) {
                if (k == currLen - 1) {
                    return ch;
                }
                currLen = prevLen;
            } else if (ch == '*') {
                currLen = prevLen;
            } else if (ch == '#') {
                currLen = prevLen;
                if (k >= currLen) {
                    k %= currLen;
                }
            } else if (ch == '%') {
                k = currLen - 1 - k;
                currLen = prevLen;
            }
        }
        
        return '.';
    }
}
