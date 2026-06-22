/*
Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible.

You can use each character in text at most once. Return the maximum number of instances that can be formed.

 

Example 1:



Input: text = "nlaebolko"
Output: 1
Example 2:



Input: text = "loonbalxballpoon"
Output: 2
Example 3:

Input: text = "leetcode"
Output: 0
 

Constraints:

1 <= text.length <= 104
text consists of lower case English letters only.
*/

class Solution {
    public int maxNumberOfBalloons(String text) {
        int[] counts = new int[5]; // Indices for: b, a, l, o, n
        
        for (char c : text.toCharArray()) {
            if (c == 'b') counts[0]++;
            else if (c == 'a') counts[1]++;
            else if (c == 'l') counts[2]++;
            else if (c == 'o') counts[3]++;
            else if (c == 'n') counts[4]++;
        }
        
        // 'l' and 'o' are needed twice per word
        counts[2] /= 2; 
        counts[3] /= 2; 
        
        // Find the minimum count
        int minBalloons = counts[0];
        for (int i = 1; i < 5; i++) {
            if (counts[i] < minBalloons) {
                minBalloons = counts[i];
            }
        }
        
        return minBalloons;
    }
}
