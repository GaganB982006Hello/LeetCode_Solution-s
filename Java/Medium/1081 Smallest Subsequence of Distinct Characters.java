/*
Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.

 

Example 1:

Input: s = "bcabc"
Output: "abc"
Example 2:

Input: s = "cbacdcbc"
Output: "acdb"
 

Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters.
*/

class Solution {
    public String smallestSubsequence(String s) {
        // 1. First store the string in a character array
        char[] chars = s.toCharArray();
        
        int[] lastOccurrence = new int[26];
        boolean[] inStack = new boolean[26];
        
        // Find the last index of every character using our new array
        for (int i = 0; i < chars.length; i++) {
            lastOccurrence[chars[i] - 'a'] = i;
        }
        
        StringBuilder sb = new StringBuilder();
        
        // 2. Using a for loop and if conditions to add the correct characters
        for (int i = 0; i < chars.length; i++) {
            char c = chars[i];
            
            // If the character is already in our final string, skip it
            if (inStack[c - 'a']) {
                continue;
            }
            
            // If the current character is smaller than the last added character, 
            // and the last added character appears again later, remove it.
            while (sb.length() > 0 && sb.charAt(sb.length() - 1) > c && lastOccurrence[sb.charAt(sb.length() - 1) - 'a'] > i) {
                // Mark as removed
                inStack[sb.charAt(sb.length() - 1) - 'a'] = false;
                sb.deleteCharAt(sb.length() - 1);
            }
            
            // Add the string character and mark it as visited
            sb.append(c);
            inStack[c - 'a'] = true;
        }
        
        // Return the constructed string
        return sb.toString();
    }
}
