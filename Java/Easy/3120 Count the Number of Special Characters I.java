/*
You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.

Return the number of special letters in word.

 

Example 1:

Input: word = "aaAbcBC"

Output: 3

Explanation:

The special characters in word are 'a', 'b', and 'c'.

Example 2:

Input: word = "abc"

Output: 0

Explanation:

No character in word appears in uppercase.

Example 3:

Input: word = "abBCab"

Output: 1

Explanation:

The only special character in word is 'b'.

 

Constraints:

1 <= word.length <= 50
word consists of only lowercase and uppercase English letters.
*/

class Solution {
    public int numberOfSpecialChars(String word) {
        boolean[] lowerSeen = new boolean[26];
        boolean[] upperSeen = new boolean[26];
        
        // Mark the presence of each character
        for (char ch : word.toCharArray()) {
            if (ch >= 'a' && ch <= 'z') {
                lowerSeen[ch - 'a'] = true;
            } else if (ch >= 'A' && ch <= 'Z') {
                upperSeen[ch - 'A'] = true;
            }
        }
        
        int specialCount = 0;
        // Count how many alphabet positions have both flags set to true
        for (int i = 0; i < 26; i++) {
            if (lowerSeen[i] && upperSeen[i]) {
                specialCount++;
            }
        }
        
        return specialCount;
    }
}
