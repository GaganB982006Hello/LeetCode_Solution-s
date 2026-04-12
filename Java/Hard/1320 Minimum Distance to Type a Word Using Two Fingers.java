/*
You have a keyboard layout as shown above in the X-Y plane, where each English uppercase letter is located at some coordinate.

For example, the letter 'A' is located at coordinate (0, 0), the letter 'B' is located at coordinate (0, 1), the letter 'P' is located at coordinate (2, 3) and the letter 'Z' is located at coordinate (4, 1).
Given the string word, return the minimum total distance to type such string using only two fingers.

The distance between coordinates (x1, y1) and (x2, y2) is |x1 - x2| + |y1 - y2|.

Note that the initial positions of your two fingers are considered free so do not count towards your total distance, also your two fingers do not have to start at the first letter or the first two letters.

 

Example 1:

Input: word = "CAKE"
Output: 3
Explanation: Using two fingers, one optimal way to type "CAKE" is: 
Finger 1 on letter 'C' -> cost = 0 
Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2 
Finger 2 on letter 'K' -> cost = 0 
Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1 
Total distance = 3
Example 2:

Input: word = "HAPPY"
Output: 6
Explanation: Using two fingers, one optimal way to type "HAPPY" is:
Finger 1 on letter 'H' -> cost = 0
Finger 1 on letter 'A' -> cost = Distance from letter 'H' to letter 'A' = 2
Finger 2 on letter 'P' -> cost = 0
Finger 2 on letter 'P' -> cost = Distance from letter 'P' to letter 'P' = 0
Finger 1 on letter 'Y' -> cost = Distance from letter 'A' to letter 'Y' = 4
Total distance = 6
 

Constraints:

2 <= word.length <= 300
word consists of uppercase English letters.
*/

class Solution {
    private Integer[][][] memo;

    public int minimumDistance(String word) {
        memo = new Integer[word.length()][27][27];
        return solve(word, 0, 26, 26); // 26 represents a 'null' or 'off-keyboard' starting position
    }

    private int solve(String word, int idx, int f1, int f2) {
        if (idx == word.length()) return 0;
        if (memo[idx][f1][f2] != null) return memo[idx][f1][f2];

        int curr = word.charAt(idx) - 'A';

        // Option 1: Move Finger 1 to curr
        int moveF1 = getDist(f1, curr) + solve(word, idx + 1, curr, f2);

        // Option 2: Move Finger 2 to curr
        int moveF2 = getDist(f2, curr) + solve(word, idx + 1, f1, curr);

        return memo[idx][f1][f2] = Math.min(moveF1, moveF2);
    }

    private int getDist(int from, int to) {
        if (from == 26) return 0; // Starting cost is free
        int x1 = from / 6, y1 = from % 6;
        int x2 = to / 6, y2 = to % 6;
        return Math.abs(x1 - x2) + Math.abs(y1 - y2);
    }
}
